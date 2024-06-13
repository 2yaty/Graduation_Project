import multiprocessing as mp
from camera_process import camera_process
from traffic_sign_process import traffic_sign_process
from lane_departure_process import lane_departure_process
from stm_process import stm_process
from dmrs_process import dmrs_process
import serial
import threading

if __name__ == "__main__":
    ip_address = "tcp://127.0.0.1:8888"  # Replace with your IP camera address
    # Create queues
    traffic_queue = mp.Queue(maxsize=10)
    lane_queue = mp.Queue(maxsize=10)
    dmrs_queue = mp.Queue(maxsize=10)

        # Configure serial port
    ser = serial.Serial(
        port='/dev/ttyS0',  # replace with your port name
        baudrate=19200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )
    # Create processes
    camera_proc = mp.Process(target=camera_process,
                             args=(traffic_queue, lane_queue,ip_address))
    traffic_proc = mp.Process(
        target=traffic_sign_process, args=(traffic_queue,))
    lane_proc = mp.Process(target=lane_departure_process, args=(lane_queue,))
    #stm_proc = threading.Thread(target=stm_process, args=(ser, dmrs_queue))
    #dmrs_proc = threading.Thread(target=dmrs_process, args=(dmrs_queue,))
    
    # Start processes
    camera_proc.start()
    traffic_proc.start()
    lane_proc.start()
    #stm_proc.start()
    #dmrs_proc.start()
    
    # Join processes
    camera_proc.join()
    traffic_proc.join()
    lane_proc.join()
    #stm_proc.join()
    #dmrs_proc.join()

