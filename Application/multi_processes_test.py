import multiprocessing
import threading
import queue
import time

def sender_thread(queue):
    message = "Hello from sender thread!"
    queue.put(message)
    print(f"Sender thread sent: {message}")

def receiver_thread(queue):
    message = queue.get()
    print(f"Receiver thread received: {message}")

def process_func(queue1, queue2):
    sender = threading.Thread(target=sender_thread, args=(queue1,))
    receiver = threading.Thread(target=receiver_thread, args=(queue2,))
    sender.start()
    receiver.start()
    sender.join()
    receiver.join()

if __name__ == "__main__":
    # Create queues
    queue1 = multiprocessing.Queue()
    queue2 = multiprocessing.Queue()

    # Create processes
    process1 = multiprocessing.Process(target=process_func, args=(queue1, queue2))
    process2 = multiprocessing.Process(target=process_func, args=(queue2, queue1))

    # Start processes
    process1.start()
    process2.start()

    # Join processes
    process1.join()
    process2.join()
