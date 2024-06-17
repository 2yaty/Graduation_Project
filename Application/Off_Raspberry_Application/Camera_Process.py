import cv2
import multiprocessing as mp
import time



def camera_process(traffic_queue, lane_queue, ip_address):
    cap = cv2.VideoCapture(ip_address)

    while True:
        ret, frame = cap.read()
        if not ret:
            continue

        # Resize frame if needed
        frame = cv2.resize(frame, (640, 480))

        # Put the frame in both queues
        if not traffic_queue.full():
            traffic_queue.put(frame)
        if not lane_queue.full():
            lane_queue.put(frame)

        # Sleep for a specified interval before capturing next image
        time.sleep(0.1)

        # Display the frame for debugging
        #cv2.imshow('Camera Frame', frame)

        # Exit on 'q' key press
        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #     break

    # cap.release()
    # cv2.destroyAllWindows()

if __name__ == "__main__":
    ip_address = "tcp://127.0.0.1:8888"  # Replace with your IP camera address
    traffic_queue = mp.Queue(maxsize=10)
    lane_queue = mp.Queue(maxsize=10)
    p = mp.Process(target=camera_process, args=(traffic_queue, lane_queue, ip_address))
    p.start()
    p.join()
