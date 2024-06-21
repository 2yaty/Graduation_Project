import cv2
import multiprocessing as mp
import  traffic_model  # Importing the traffic model
from main import show

# Mapping of class IDs to names
class_names = [[0,'Green Light'], [1,'Red Light'],[10, 'Speed Limit 10'],[100, 'Speed Limit 100'],[110, 'Speed Limit 110'], [120,'Speed Limit 120'], 
               [20,'Speed Limit 20'],[30, 'Speed Limit 30'],[40, 'Speed Limit 40'],[50, 'Speed Limit 50'],[60, 'Speed Limit 60'], [70,'Speed Limit 70'], 
               [80,'Speed Limit 80'], [90,'Speed Limit 90'],[2, 'Stop']]


def traffic_sign_process(queue ,display_output_queue,trip_statistics,speed):

    def handle_traffic_warnings(classId):
            # Get data from the traffic output queue
            
            # TODO: compare the speed with the speed limit and increment the speed limit violation
            if (class_names[classId][0] > 2) :
                curr_speed = class_names[classId][0]
                if curr_speed > speed.value:
                    trip_statistics['speed_limit_violation'] += 1


            display_output_queue.put(class_names[classId][1])
            # Example: Print the data
            # print("Traffic Output:", data)


    while True:
        if not queue.empty():
            frame = queue.get()

            # Run the traffic sign model
            traffic_sign = traffic_model.predict_traffic_sign(frame)
            # print("Traffic Sign:", traffic_sign) # TODO: test the output and see what it looks like and comment this line

             # Process the results
            for result in traffic_sign:
                for detection in result.boxes:
                    class_id = int(detection.cls)
                    confidence = detection.conf
                    bbox = detection.xyxy
                    handle_traffic_warnings(class_id)
                    sign_name = class_names[class_id]
                    print(f"Detected Sign: {sign_name[1]}, Confidence: {confidence:.2f}, BBox: {bbox}")
                    
            
            if show:
                cv2.imshow('Traffic Sign Frame', frame)

            # if cv2.waitKey(1) & 0xFF == ord('q'):
            #     break


if __name__ == "__main__":
    queue = mp.Queue(maxsize=10)
    p = mp.Process(target=traffic_sign_process, args=(queue,))
    p.start()
    p.join()
