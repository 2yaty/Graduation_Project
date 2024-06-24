import pandas as pd
import numpy as np
import pickle
import multiprocessing as mp

def dmrs_process(data_queue, trip_statistics):
    last = [0]  # Using a list to allow modification inside the inner function

    def handle_dmrs_warnings(data):
        nonlocal last  # Reference the outer 'last' variable
        predicted_actions = {
            1: 'suddenAcceleration',
            2: 'sudden_right_turn',
            3: 'aggTL',
            4: 'suddenBraking',
            5: 'normalDriving'
        }
        if data != last[0]:
            print("DMRS: ", predicted_actions[data])
            last[0] = data  # Update the 'last' value
        else:
            return
        
        # Update trip statistics based on prediction
        action_keys = {
            1: 'suddenAcceleration',
            2: 'aggTR',
            3: 'aggTL',
            4: 'suddenBraking',
            5: 'normalDriving'
        }
        if data in action_keys:
            trip_statistics[action_keys[data]] += 1

    # Load your exported model
    with open('/home/pi/Desktop/Final_application/Graduation_Project/Application/Off_Raspberry_Application/mobile_2_model_2_with.pkl', 'rb') as file:
        model = pickle.load(file)

    data_list = []
    while True:
        if not data_queue.empty():
            data_values = data_queue.get()
            data_list.append(data_values)

            if len(data_list) >= 6:  # Assuming window size of 6 for the model
                subset_df = pd.DataFrame(data_list[-6:], columns=['GyroX', 'GyroY', 'GyroZ', 'AccX', 'AccY', 'AccZ'])
                subset_df /= 1.15  # Normalize all data by 1.15

                statistical_data = {
                    'mean': subset_df.mean().tolist(),
                    'cov': subset_df.cov().values.flatten().tolist(),
                    'skew': subset_df.skew().tolist(),
                    'kurtosis': subset_df.kurtosis().tolist(),
                    'sum': subset_df.sum().tolist(),
                    'min': subset_df.min().tolist(),
                    'max': subset_df.max().tolist(),
                    'var': subset_df.var().tolist(),
                    'median': subset_df.median().tolist(),
                    'std': subset_df.std().tolist(),
                }
                input_data = np.array(list(statistical_data.values())).reshape(1, -1)
                prediction = model.predict(input_data)[0]
                handle_dmrs_warnings(prediction)
                data_list.pop(0)  # Remove the oldest data entry

if __name__ == "__main__":
    data_queue = mp.Queue(maxsize=10)
    trip_statistics = {
        'suddenAcceleration': 0,
        'aggTR': 0,
        'aggTL': 0,
        'suddenBraking': 0,
        'normalDriving': 0
    }
    dmrs_process(data_queue, trip_statistics)
