import cv2
import multiprocessing as mp
import lane_model  # Importing the lane departure model
import matplotlib.image as mpimg
from show_var import show

def lane_departure_process(queue,display_output_queue):

    def handle_lane_output(data):
            if data == False:
                display_output_queue.put("You are out of lane")


    while True:
        if not queue.empty():
            frame = queue.get()

            # Run the lane departure model
            annotatedFrame, isInLane = lane_model.predict_lane_departure(frame)
            # print("Lane Departure:", lane_departure)


            handle_lane_output(isInLane)


            # # For debugging
            # cv2.imshow('Lane Departure Frame', frame)
            if show:
                cv2.imshow('Lane Departure Annotated Frame', annotatedFrame)
            
            
                
        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #         break    


if __name__ == "__main__":
    queue = mp.Queue(maxsize=10)
    p = mp.Process(target=lane_departure_process, args=(queue,))
    p.start()
    queue.put(mpimg.imread(r'D:\Faculty\7th Semester\Final_application\data\maxresdefault.jpg'))
    p.join()
