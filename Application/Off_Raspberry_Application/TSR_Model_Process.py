import cv2
import multiprocessing as mp
import  traffic_model  # Importing the traffic model
from main import show

def traffic_sign_process(queue ,display_output_queue,trip_statistics,speed):

    def handle_traffic_warnings(data):
            # Get data from the traffic output queue
            
            # TODO: compare the speed with the speed limit and increment the speed limit violation
            if data == 'speed_limit_violation':
                trip_statistics['speed_limit_violation'] += 1


            display_output_queue.put(data)
            # Example: Print the data
            # print("Traffic Output:", data)


    while True:
        if not queue.empty():
            frame = queue.get()

            # Run the traffic sign model
            traffic_sign = traffic_model.predict_traffic_sign(frame)
            print("Traffic Sign:", traffic_sign) # TODO: test the output and see what it looks like and comment this line
            handle_traffic_warnings(traffic_sign)
            if show:
                cv2.imshow('Traffic Sign Frame', frame)

            # if cv2.waitKey(1) & 0xFF == ord('q'):
            #     break


if __name__ == "__main__":
    queue = mp.Queue(maxsize=10)
    p = mp.Process(target=traffic_sign_process, args=(queue,))
    p.start()
    p.join()
