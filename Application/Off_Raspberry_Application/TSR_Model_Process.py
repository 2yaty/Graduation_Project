import time
import cv2
import multiprocessing as mp
import  traffic_model  # Importing the traffic model
from show_var import show

# Mapping of class IDs to names
class_names = [[0,'Green Light'], [1,'Red Light'],[10, 'Speed Limit 10'],[100, 'Speed Limit 100'],[110, 'Speed Limit 110'], [120,'Speed Limit 120'], 
               [20,'Speed Limit 20'],[30, 'Speed Limit 30'],[40, 'Speed Limit 40'],[50, 'Speed Limit 50'],[60, 'Speed Limit 60'], [70,'Speed Limit 70'], 
               [80,'Speed Limit 80'], [90,'Speed Limit 90'],[2, 'Stop']]

CUR_SPEED_LIMIT= 120
LAST_VIOLATION_TIME = 0

def traffic_sign_process(queue ,display_output_queue,trip_statistics,speed):

    def handle_traffic_warnings(classId):
            # Get data from the traffic output queue
            
            if (class_names[classId][0] > 2) :
                CUR_SPEED_LIMIT = class_names[classId][0]
                if  speed.value > CUR_SPEED_LIMIT:
                    if (time.time() - LAST_VIOLATION_TIME) > 10:
                        trip_statistics['speedLimitViolation'] += 1
                        display_output_queue.put("Speed Limit Violation, Speed Limit is "+str(CUR_SPEED_LIMIT)+" km/h, Your speed is "+str(speed.value)+" km/h")
                        LAST_VIOLATION_TIME = time.time()


            display_output_queue.put(class_names[classId][1])
            # Example: Print the data
            # print("Traffic Output:", data)


    while True:
        if not queue.empty():
            frame = queue.get()

            # Run the traffic sign model
            traffic_sign = traffic_model.predict_traffic_sign(frame)

             # Process the results
            for result in traffic_sign:
                for detection in result.boxes:
                    class_id = int(detection.cls)
                    handle_traffic_warnings(class_id)
        
            if True:
                cv2.imshow('Traffic Sign Frame', frame)

            # if cv2.waitKey(1) & 0xFF == ord('q'):
            #     break


if __name__ == "__main__":
    queue = mp.Queue(maxsize=10)
    p = mp.Process(target=traffic_sign_process, args=(queue,))
    p.start()
    p.join()
