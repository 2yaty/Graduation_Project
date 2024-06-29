import os
import signal
import time
import serial
import struct
import json
import multiprocessing
import threading
from threading import Timer
import multiprocessing as mp

zero_speed_start_time  = 0
# the process takes the serial port, the queue that is shared with the DMRS model and the speed variable that is shared with the Warning model
def stm_process(ser, dmrs_queue,display_output_queue,speed,StartEvent, StopEvent):
    mpu_rate = True

    def delayed_function(display_output_queue):
        time.sleep(1)  # Delay execution for 5 seconds
        display_output_queue.put("*F0*")

    def FCW_thread(queue,display_output_queue):
        while True:
            warning_level = queue.get()
            display_output_queue.put("*F"+str(int(warning_level*33.3))+"*")
            for i in range(warning_level):
                display_output_queue.put("*fV50*")
            
            # Create a thread that runs the delayed_function
            delayed_thread = threading.Thread(target=delayed_function, args=(display_output_queue,))
            # Start the thread
            delayed_thread.start()

    def check_speed( new_speed):
                zero_speed_start_time = 0

                # Terminate the running processes if the speed is zero for more than 60 seconds
                if speed.value == 0 and new_speed == 0:
                    if zero_speed_start_time == 0:
                        zero_speed_start_time = time.time()
                    else:
                        if (time.time() - zero_speed_start_time) > 60:
                            parent_pid = os.getppid()
                            # os.kill(parent_pid, signal.SIGTERM)
                            display_output_queue.put("do you want to end the trip?")
                else:
                    zero_speed_start_time = 0
                    speed.value = new_speed


    def process_data(data,fcw_queue):
        nonlocal mpu_rate
        # Parse the JSON data
        parsed_data = json.loads(data)

        # Check the source of the data
        source = parsed_data.get('from')

        # Start the models if STM sends a start signal
        if source == 'engine':
            # parent_pid = os.getppid()  # Get the parent process ID
            # os.kill(parent_pid, signal.SIGINT)
            state = parsed_data.get('data')
            print("the state of the engine: ", state )

            if state == 'start':
                StartEvent.set()
                display_output_queue.put("*C\nthe engine is starting ...\n*")
            if state == 'end':
                display_output_queue.put("*C\nthe engine is stopping ...\n*")
                StopEvent.set()


        if source == 'speed': #update the speed 
            #TODO: get the speed properly
            new_speed = int(parsed_data.get('data'))
            # print("the recieved speed is: ", new_speed)
            check_speed(new_speed)
            display_output_queue.put("*S"+str(int(new_speed*12.5))+"*")
            
            
        if source == 'FCW':
            
            # Decode bytes to string
            json_str = data.decode()

            # Parse the JSON to get the inner 'data' string
            outer_data = json.loads(json_str)
            inner_data_str = outer_data['data']

            # Correct the single quotes and other formatting issues in the 'data' string
            inner_data_str = inner_data_str.replace("'", '"')

            # Parse the corrected JSON string
            inner_data = json.loads(inner_data_str)

            # Extract the 'warning_level'
            warning_level = inner_data['warning_level']
            fcw_queue.put(warning_level)

            
            

        # get MPU data and put it in the queue
        if source == 'MPU':
            
            mpu_data = parsed_data.get('data')
            # print(mpu_data)

            # Replace single quotes with double quotes
            mpu_data_json = mpu_data.replace("'", '"')

            # Convert the JSON string to a dictionary
            mpu_data_dict = json.loads(mpu_data_json)
            values = [float(mpu_data_dict['GX']), float(mpu_data_dict['GY']),
                    float(mpu_data_dict['GZ']), float(mpu_data_dict['AX']), float(mpu_data_dict['AY']), float(mpu_data_dict['AZ'])]

            if not dmrs_queue.full():
                
                dmrs_queue.put(values)


    def send_data_to_STM(display_output_queue):
        ser = serial.Serial(
        port='/dev/ttyAMA3',  # replace with your port name
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
        )
        display_output_queue.put("*C\nRaspberry is ready\n*")
        while True:
            # Get the data from the display output queue
            data = display_output_queue.get()
            ser.write(data.encode("utf-8"))
    
    # Create a thread to send the data to the STM
    send_data_thread = threading.Thread(target=send_data_to_STM , args=(display_output_queue,))
    send_data_thread.start()

    fcw_queue = mp.Queue(maxsize=10)

    fcw_thread = threading.Thread(target=FCW_thread , args=(fcw_queue,display_output_queue))
    fcw_thread.start()

    while True:
        # TODO: if there any problem with the serial port, terminate all the models
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
                        process_data(payload,fcw_queue)
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
