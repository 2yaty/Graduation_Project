import cv2
import multiprocessing as mp
import traffic_app  # Importing the traffic model


def traffic_sign_process(queue):
    while True:
        if not queue.empty():
            frame = queue.get()

            # Run the traffic sign model
            traffic_sign = traffic_app.predict_traffic_sign(frame)
            print("Traffic Sign:", traffic_sign)

            # For debugging
            cv2.imshow('Traffic Sign Frame', frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break


if __name__ == "__main__":
    queue = mp.Queue(maxsize=10)
    p = mp.Process(target=traffic_sign_process, args=(queue,))
    p.start()
    p.join()
