import serial
import struct
import json
import multiprocessing
import threading

# Function to process incoming data


def process_data(data, queue):
    # Parse the JSON data
    parsed_data = json.loads(data)

    # Check the source of the data
    source = parsed_data.get('from')

    # print(parsed_data)
    if source == 'MPU':
        mpu_data = parsed_data.get('data')
        # print(type(mpu_data))
        # Replace single quotes with double quotes
        mpu_data_json = mpu_data.replace("'", '"')

        # Convert the JSON string to a dictionary
        mpu_data_dict = json.loads(mpu_data_json)
        values = [float(mpu_data_dict['AX']), float(mpu_data_dict['AY']),
                  float(mpu_data_dict['AZ']), float(mpu_data_dict['GX']), float(mpu_data_dict['GY']), float(mpu_data_dict['GZ'])]

        queue.put(values)
        print(values)


def stm_process(ser, dmrs_queue):
    while True:
        # Read header
        header = ser.read(1)
        if header != b'\xAA':
            continue

        header = ser.read(1)
        if header == b'U':
            # Read payload length
            length = ser.read(1)
            if length:
                length = struct.unpack('B', length)[0]
                # Read payload
                payload = ser.read(length)
                # Read checksum
                checksum = ser.read(1)
                if checksum:
                    checksum = struct.unpack('B', checksum)[0]

                    # Validate checksum (simple sum of payload bytes)
                    if checksum == sum(payload) & 0xFF:
                        process_data(payload, dmrs_queue)
                    else:
                        print("Checksum error")
            else:
                print("Error reading length")
        else:
            print("Invalid header")
            pass

##################################### FOR TESTING #####################################


def receiver_process(queue):
    while True:
        message = queue.get()
        # print(f"Receiver thread received: {message}")


if __name__ == "__main__":
    queue1 = multiprocessing.Queue()

    # Configure serial port
    ser = serial.Serial(
        port='/dev/ttyS0',  # replace with your port name
        baudrate=19200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )

    transmitter = threading.Thread(target=stm_process, args=(ser, queue1))
    receiver = threading.Thread(target=receiver_process, args=(queue1,))

    transmitter.start()
    receiver.start()

    # Wait for 10 seconds
    transmitter.join()
    receiver.join()
