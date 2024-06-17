import multiprocessing as mp
import signal
from Camera_Process import camera_process
from TSR_Model_Process import traffic_sign_process
from LDW_Model_Process import lane_departure_process
from STM_Process import stm_process
from MPU_Model_Process import dmrs_process
from Warning_Process import warning_process
import serial
import threading
import TripStatistics
import time
from datetime import datetime

show = True

if __name__ == "__main__":
    
    ip_address = "tcp://127.0.0.1:8888"  # Replace with your IP camera address

    # Configure serial port
    ser = serial.Serial(
        port='/dev/ttyS0',  # replace with your port name
        baudrate=19200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )

    with mp.Manager() as manager:
        shared_trip = manager.Namespace()
        shared_trip.trip = None

    speed = mp.Value('d', 0.0)

    # Create input queues
    traffic_queue = mp.Queue(maxsize=10)
    lane_queue = mp.Queue(maxsize=10)
    dmrs_queue = mp.Queue(maxsize=10)

    # Create output queues
    traffic_output_queue = mp.Queue(maxsize=10)
    lane_output_queue = mp.Queue(maxsize=10)
    dmrs_output_queue = mp.Queue(maxsize=10)
    display_output_queue = mp.Queue(maxsize=10)


    camera_proc = mp.Process(target=camera_process,
                            args=(traffic_queue, lane_queue,ip_address))
    traffic_proc = mp.Process(
        target=traffic_sign_process, args=(traffic_queue,traffic_output_queue))
    lane_proc = mp.Process(target=lane_departure_process, args=(lane_queue,lane_output_queue))
    stm_proc = threading.Thread(target=stm_process, args=(ser, dmrs_queue,speed))
    dmrs_proc = threading.Thread(target=dmrs_process, args=(dmrs_queue,dmrs_output_queue))
    warning_proc = mp.Process(target=warning_process, args=(dmrs_output_queue,traffic_output_queue,lane_output_queue,display_output_queue,speed , shared_trip))

    def start_models_processes():
        shared_trip.trip  = TripStatistics.TripStatistics()
        shared_trip.setStart_time(datetime.now())
        dmrs_proc.start()
        camera_proc.start()
        traffic_proc.start()
        lane_proc.start()

    # TODO: Test these signals to see if they work as expected
    signal.signal(signal.SIGINT, start_models_processes) # TODO: make a custom signals for the start and stop of the models

    def stop_models_processes():
        trip.setEnd_time(datetime.now())
        trip.calculateOverAllScore()
        #TODO: send the trip statistics to the server
        dmrs_proc.terminate()
        camera_proc.terminate()
        traffic_proc.terminate()
        lane_proc.terminate()
        # empty the queues
        while not traffic_queue.empty():
            traffic_queue.get()

        while not lane_queue.empty():
            lane_queue.get()
        
        while not dmrs_queue.empty():
            dmrs_queue.get()
        
        while not traffic_output_queue.empty():
            traffic_output_queue.get()
        
        while not lane_output_queue.empty():
            lane_output_queue.get()
        
        while not dmrs_output_queue.empty():
            dmrs_output_queue.get()
        
        trip = None
        
    signal.signal(signal.SIGTERM, stop_models_processes)

    stm_proc.start()

    
        


    

    
    # Join processes
    camera_proc.join()
    traffic_proc.join()
    lane_proc.join()
    stm_proc.join()
    dmrs_proc.join()

