import json
import multiprocessing as mp
import signal

import requests
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
serial_number = "12345678910"

def send_shared_trip_to_theWeb(shared_trip,display_output_queue):
    # API endpoint URL
    url = "https://dmrs-c487bb5f6150.herokuapp.com/api/v1/trips"

    

    # API key for authentication
    api_key = "e9H3pMSRS7Bxd1XXCUVPVCIT0ntESkjEB0h0JNqyW2tDu6rLW0i48EJxQFQZkRMfDrTuy9lBivLJmQ54Bjo6sDEeAsWIGafszZE1MEID1OIXkMXHyJOH6m7CHuYFCq3o"


    # Prepare the headers with the API key
    headers = {
        "CAR-API-KEY": api_key
    }

    # shared_trip["serialNumber"] = serial_number

    try:
        # Send the POST request to the API endpoint with headers
        response = requests.post(url, data=shared_trip, headers=headers)

        # Check the response status code
        if response.status_code == 200:
            print("Shared trip data sent successfully!")
            display_output_queue.put("trip data sent successfully!")
        else:
            print("Failed to send shared trip data. Status code:", response.status_code, "response content: ",response.content,response.text)
            display_output_queue.put("Failed to send trip data. Status code:", response.status_code)

    except requests.exceptions.RequestException as e:
        print("An error occurred while sending shared trip data:", str(e))
        display_output_queue.put("An error occurred while sending trip data to the web, could be no internet connection")



def calculate_overall_score(trip_statistics):
    #TODO: calculate the overall score
    pass

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

    manager = mp.Manager()
    shared_trip = manager.dict({
            "start_time": None,
            "end_time": None,
            "suddenBraking": 0,
            "suddenAcceleration": 0,
            "aggTL": 0,
            "aggTR": 0,
            "speedLimitViolation": 0,
            "normalDriving": 0,
            "totalScore": 0
        }
)


    speed = manager.Value('d', 0.0)

    # Create input queues
    traffic_queue = mp.Queue(maxsize=10)
    lane_queue = mp.Queue(maxsize=10)
    dmrs_queue = mp.Queue(maxsize=10)
    display_output_queue = mp.Queue(maxsize=10)

    StartEvent = mp.Event()
    StopEvent = mp.Event()

    


    camera_proc = mp.Process(target=camera_process,
                            args=(traffic_queue, lane_queue,ip_address))
    traffic_proc = mp.Process(
        target=traffic_sign_process, args=(traffic_queue,display_output_queue,shared_trip,speed))
    lane_proc = mp.Process(target=lane_departure_process, args=(lane_queue,display_output_queue))
    stm_proc = mp.Process(target=stm_process, args=(ser, dmrs_queue, display_output_queue,speed, StartEvent, StopEvent))
    dmrs_proc = mp.Process(target=dmrs_process, args=(dmrs_queue,shared_trip))
    

    stm_proc.start()
    
    StartEvent.wait()


    shared_trip["start_time"] = datetime.now().isoformat()
    dmrs_proc.start()
    camera_proc.start()
    traffic_proc.start()
    lane_proc.start()
    StartEvent.clear()


    StopEvent.wait()
    shared_trip['end_time'] = datetime.now().isoformat()
    final_trip = {
            
            "start_time": shared_trip['start_time'],
            "end_time": shared_trip['end_time'],
            "suddenBraking": shared_trip['suddenBraking'],
            "suddenAcceleration": shared_trip['suddenAcceleration'],
            "aggTL": shared_trip['aggTL'],
            "aggTR": shared_trip['aggTR'],
            "speedLimitViolation": shared_trip['speedLimitViolation'],
            "normalDriving": shared_trip['normalDriving'],
            "totalScore": shared_trip['totalScore'],
            "serialNumber": serial_number
        }
    print("the shared trip data: ", final_trip)
    calculate_overall_score(shared_trip)
    send_shared_trip_to_theWeb(json.dumps(final_trip),display_output_queue)
    dmrs_proc.kill()
    camera_proc.kill()
    traffic_proc.kill()
    lane_proc.kill()
    # empty the queues
    while not traffic_queue.empty():
        traffic_queue.get()

    while not lane_queue.empty():
        lane_queue.get()
    
    while not dmrs_queue.empty():
        dmrs_queue.get()
    

    StopEvent.clear()
        
    manager.shutdown()

    

    
        


    

    
    # Join processes
    # camera_proc.join()
    # traffic_proc.join()
    # lane_proc.join()
    # stm_proc.join()
    # dmrs_proc.join()

