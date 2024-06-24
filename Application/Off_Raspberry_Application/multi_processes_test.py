from datetime import datetime
import json
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

# from multiprocessing import Process, Manager

# class Student:
#     def __init__(self, name):
#         self.name = name

# def update_student(shared_student):
#     shared_student.name = 'Updated Name'

# if __name__ == '__main__':
#     with Manager() as manager:
#         # Create a proxy for the Student object
#         student_proxy = manager.Namespace()
#         student_proxy.name = 'Original Name'
        
#         process = Process(target=update_student, args=(student_proxy,))
#         process.start()
#         process.join()

#         print(student_proxy.name)  # Should print 'Updated Name'

# import multiprocessing
# import os
# import time

# # Function for process 1
# def process_1(event):
#     print(f'Process 1 with PID: {os.getpid()}')
#     while True:
#         event.wait()  # Wait for the event to be set
#         print(f'Process 1 received custom signal')
#         event.clear()  # Clear the event after handling

# # Function for process 2
# def process_2(event):
#     print(f'Process 2 with PID: {os.getpid()}')
#     time.sleep(3)  # Wait a few seconds before sending custom signal
#     print(f'Process 2 sending custom signal to Process 1')
#     event.set()  # Set the event to simulate sending a signal

# if __name__ == '__main__':
#     # Create an Event object
#     event = multiprocessing.Event()

#     # Create process 1 and pass the event
#     p1 = multiprocessing.Process(target=process_1, args=(event,))
#     p1.start()

#     # Create process 2 and pass the event
#     p2 = multiprocessing.Process(target=process_2, args=(event,))
#     p2.start()

#     # Wait for processes to complete
#     p1.join()
#     p2.join()


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










# import multiprocessing
# import time
# import os
# from multiprocessing.managers import BaseManager

# class MyManager(BaseManager):
#     pass
# # Define the Student class
# class Student:
#     def __init__(self, name, age, grade):
#         self.name = name
#         self.age = age
#         self.grade = grade

#     def __repr__(self):
#         return f"Student(name={self.name}, age={self.age}, grade={self.grade})"

# # Function to modify the student object in process 1
# def process_1(shared_student):
#     print(f'Process 1 with PID: {os.getpid()}')
#     time.sleep(2)  # Simulate some work
#     shared_student.name = "Alice"
#     shared_student.age = 21
#     shared_student.grade = "A"
#     print(f'Process 1 updated student to: {shared_student}')

# # Function to read the student object in process 2
# def process_2(shared_student):
#     print(f'Process 2 with PID: {os.getpid()}')
#     time.sleep(4)  # Ensure process 1 has modified the object
#     print(f'Process 2 reads student as: {shared_student}')

# if __name__ == '__main__':
#     # Create a Manager object and register the Student class
#     MyManager.register('Student', Student)
#     with MyManager() as manager:
#         # Create a shared Student object
#         shared_student = manager.Student("John", 20, "B")
#         print(f'Main process initial student: {shared_student}')

#         # Create and start process 1
#         p1 = multiprocessing.Process(target=process_1, args=(shared_student,))
#         p1.start()

#         # Create and start process 2
#         p2 = multiprocessing.Process(target=process_2, args=(shared_student,))
#         p2.start()

#         # Wait for both processes to complete
#         p1.join()
#         p2.join()

#         print(f'Main process final student: {shared_student}')


# from multiprocessing.managers import BaseManager

# class MathsClass:
#     def add(self, x, y):
#         return x + y
#     def mul(self, x, y):
#         return x * y

# class MyManager(BaseManager):
#     pass

# MyManager.register('Maths', MathsClass)

# if __name__ == '__main__':
#     with MyManager() as manager:
#         maths = manager.Maths()
#         print(maths.add(4, 3))         # prints 7
#         print(maths.mul(7, 8))         # prints 56


# import multiprocessing
# import time
# import os
# # Define the Student class
# class Student:
#     def __init__(self, namespace):
#         self.namespace = namespace

#     @property
#     def name(self):
#         return self.namespace.name

#     @name.setter
#     def name(self, value):
#         self.namespace.name = value

#     @property
#     def age(self):
#         return self.namespace.age

#     @age.setter
#     def age(self, value):
#         self.namespace.age = value

#     @property
#     def grade(self):
#         return self.namespace.grade

#     @grade.setter
#     def grade(self, value):
#         self.namespace.grade = value

#     def __repr__(self):
#         return f"Student(name={self.name}, age={self.age}, grade={self.grade})"

# # Function to modify the student object in process 1
# def process_1(namespace):
#     student = Student(namespace)
#     print(f'Process 1 with PID: {os.getpid()}')
#     time.sleep(2)  # Simulate some work
#     student.name = "Alice"
#     student.age = 21
#     student.grade = "A"
#     print(f'Process 1 updated student to: {student}')

# # Function to read the student object in process 2
# def process_2(namespace):
#     student = Student(namespace)
#     print(f'Process 2 with PID: {os.getpid()}')
#     time.sleep(4)  # Ensure process 1 has modified the object
#     print(f'Process 2 reads student as: {student}')

# if __name__ == '__main__':
#     # Create a Manager object
#     with multiprocessing.Manager() as manager:
#         # Create a Namespace object to share the student attributes
#         namespace = manager.Namespace()
#         namespace.name = "John"
#         namespace.age = 20
#         namespace.grade = "B"

#         # Create the initial student object for the main process
#         student = Student(namespace)
#         print(f'Main process initial student: {student}')

#         # Create and start process 1
#         p1 = multiprocessing.Process(target=process_1, args=(namespace,))
#         p1.start()

#         # Create and start process 2
#         p2 = multiprocessing.Process(target=process_2, args=(namespace,))
#         p2.start()

#         # Wait for both processes to complete
#         p1.join()
#         p2.join()

#         print(f'Main process final student: {student}')


import multiprocessing
import time
import os


def process_1(student):

    print(f'Process 1 with PID: {os.getpid()}')
    time.sleep(2)  # Simulate some work
    student['name'] = "Alice"
    student['age']= 21
    student['grad']= "A"
    print(f'Process 1 updated student to: {student}')

# Function to read the student object in process 2
def process_2(student):
    print(f'Process 2 with PID: {os.getpid()}')
    time.sleep(4)  # Ensure process 1 has modified the object
    print(f'Process 2 reads student as: {student}')


def process_3(val):

    print(f'Process 3 with PID: {os.getpid()}')
    time.sleep(2)  # Simulate some work
    val.value = 10.0456775
    print(f'Process 3 updated student to: {val.value}')

# Function to read the student object in process 2
def process_4(val):
    print(f'Process 4 with PID: {os.getpid()}')
    time.sleep(4)  # Ensure process 1 has modified the object
    print(f'Process 4 reads student as: {val.value}')


if __name__ == '__main__':
    # Create a Manager object0
    manager = multiprocessing.Manager()
    # Create a Namespace object to share the student attributes
    student = manager.dict({'name': 'John', 'age': 20, 'grade': 'B'})
    
    student2 = {
            "start_time": datetime.now().isoformat(),
            "end_time": datetime.now().isoformat(),
            "suddenBraking": 0,
            "suddenAcceleration": 0,
            "aggTL": 0,
            "aggTR": 0,
            "speedLimitViolation": 0,
            "normalDriving": 0,
            "totalScore": 0
        }
    # student['name'] = "John"
    # student['age'] = 20
    # student['grade'] = "B"

    val = manager.Value('d', 0.0)
    
    data = "hiiii"
    
    print(data.encode('ascii'))

    # Create the initial student object for the main process

    print(f'Main process initial student: {json.dumps(student2)}')
    
    # Create and start process 1
    p1 = multiprocessing.Process(target=process_1, args=(student,))
    p1.start()

    # Create and start process 2
    p2 = multiprocessing.Process(target=process_2, args=(student,))
    p2.start()

    # Wait for both processes to complete
    p1.join()
    p2.join()

    print(f'Main process final student: {student}')


    print(f'Main process initial val: {val}')

    # Create and start process 1
    p1 = multiprocessing.Process(target=process_3, args=(val,))
    p1.start()

    # Create and start process 2
    p2 = multiprocessing.Process(target=process_4, args=(val,))
    p2.start()

    # Wait for both processes to complete
    p1.join()
    p2.join()

    print(f'Main process final val: {val.value}')
    manager.shutdown()

# SuperFastPython.com
# example of sharing a python object using a manager
# from time import sleep
# from random import random
# from multiprocessing import Process
# from multiprocessing.managers import BaseManager
 
# # custom manager to support custom classes
# class CustomManager(BaseManager):
#     # nothing
#     pass
 
# # custom function to be executed in a child process
# def task(number, shared_set):
#     # generate a number
#     value = random()
#     # block for a moment
#     sleep(value)
#     # store the result
#     shared_set.add((number,value))
 
# # protect the entry point
# if __name__ == '__main__':
#     # register the counter with the custom manager
#     CustomManager.register('set', set)
#     # create a new manager instance
#     with CustomManager() as manager:
#         # create a shared set instance
#         shared_set = manager.set()
#         # start some child processes
#         processes = [Process(target=task, args=(i,shared_set)) for i in range(50)]
#         # start processes
#         for process in processes:
#             process.start()
#         # wait for processes to finish
#         for process in processes:
#             process.join()
#         # all done
#         print('Done')
#         # report the results
#         print(len(shared_set._getvalue()))
#         print(shared_set)