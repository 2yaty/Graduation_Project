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



# from multiprocessing import Process, Manager

# class Student:
#     def __init__(self, name):
#         self.name = name

# def update_student(shared_student):
#     (shared_student.student).name = 'Updated Name'

# if __name__ == '__main__':
#     with Manager() as manager:
#         shared_student = manager.Namespace()
#         shared_student.student = Student('Original Name')
        
#         process = Process(target=update_student, args=(shared_student,))
#         process.start()
#         process.join()

#         print(shared_student.student.name)  # Will print 'Updated Name'

from multiprocessing import Process, Manager

class Student:
    def __init__(self, name):
        self.name = name

def update_student(shared_student):
    shared_student.name = 'Updated Name'

if __name__ == '__main__':
    with Manager() as manager:
        # Create a proxy for the Student object
        student_proxy = manager.Namespace()
        student_proxy.name = 'Original Name'
        
        process = Process(target=update_student, args=(student_proxy,))
        process.start()
        process.join()

        print(student_proxy.name)  # Should print 'Updated Name'


# if __name__ == "__main__":
    # Create queues
    # queue1 = multiprocessing.Queue()
    # queue2 = multiprocessing.Queue()

    # # Create processes
    # process1 = multiprocessing.Process(target=process_func, args=(queue1, queue2))
    # process2 = multiprocessing.Process(target=process_func, args=(queue2, queue1))

    # # Start processes
    # process1.start()
    # process2.start()

    # # Join processes
    # process1.join()
    # process2.join()
