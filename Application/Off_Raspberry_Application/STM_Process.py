import serial
import struct
import json
import multiprocessing
import threading
import time

outputQueues = {}


# Function to process incoming data
def process_data(data):
    # Parse the JSON data
    parsed_data = json.loads(data)

    # Check the source of the data
    source = parsed_data.get('from')
    
    if source == 'MPU':
        mpu_data = parsed_data.get('data')
        outputQueues['DMRS'].put(mpu_data)




def STM_Process(ser,DMRS_queue):
    outputQueues['DMRS'] = DMRS_queue
    while True:
        # Read header
        header = ser.read(1)
        if header != b'\xAA':
            continue
        # print("valid header")
        header = ser.read(1)
        # print(header == b'U' )
        if header == b'U':
            # Read payload length
            length = ser.read(1)
            # print(length)
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
                        process_data(payload)
                    else:
                        print("Checksum error")
            else:
                print("Error reading length")
        else:
            print("Invalid header")
            pass



##################################### FOR TESTING #####################################
def receiver_precess(queue):
    while True:
        message = queue.get()
        print(f"Receiver thread received: {message}")
    


if __name__ == "__main__":

    print("Starting STM process")
    queue1 = multiprocessing.Queue()

    # Configure serial port
    ser = serial.Serial(
        port='COM4',  # replace with your port name
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )

    transmitter = threading.Thread(target=STM_Process, args=(ser, queue1))
    receiver = threading.Thread(target=receiver_precess, args=(queue1,))
    
    transmitter.start()
    receiver.start()
    

    # Wait for 10 seconds
    time.sleep(10)

    # Stop the threads
    transmitter.join()
    receiver.join()
