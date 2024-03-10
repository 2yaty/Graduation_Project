import serial
import pandas as pd
import numpy as np
import pickle

# Load your exported model
window_size = 6
with open(r'mobile_2_model_2_with.pkl', 'rb') as file:
    model = pickle.load(file)

# Create a Serial object
ser = serial.Serial(
    port='COM4',  # replace with your port name
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

# Create an empty list to store data
data_list = []

while True:
    data_values = []  # Create an empty list to store one set of data

    for _ in range(6):  # Read 6 sets of floating-point values
        byte_list = []  # Create a list to store bytes for one floating-point value

        # Read bytes until carriage return '\r' is encountered
        while True:
            data_byte = ser.read(1)
            if data_byte == b'\r':
                break
            byte_list.append(data_byte)

        # Concatenate the bytes and convert to float
        float_value = float(b''.join(byte_list))
        data_values.append(float_value)

    # Append the list of data values to data_list
    data_list.append(data_values)

    if len(data_list) >= window_size:  # Check if we have at least 6 sets of data
        # Calculate statistical measures for the last 6 readings
        subset_df = pd.DataFrame(
            data_list[-window_size:], columns=['GyroX', 'GyroY', 'GyroZ', 'AccX', 'AccY', 'AccZ'])
        subset_df['AccX'] = subset_df['AccX'] / (1.15)
        subset_df['AccY'] = subset_df['AccY'] / (1.15)
        subset_df['AccZ'] = subset_df['AccZ'] / (1.15)
        subset_df['GyroX'] = subset_df['GyroX'] / (1.15)
        subset_df['GyroY'] = subset_df['GyroY'] / (1.15)
        subset_df['GyroZ'] = subset_df['GyroZ'] / (1.15)

        statistical_data = {
            'AccMeanX': subset_df['AccX'].mean(),
            'AccMeanY': subset_df['AccY'].mean(),
            'AccMeanZ': subset_df['AccZ'].mean(),

            'AccCovX': subset_df['AccX'].cov(subset_df['AccX']),
            'AccCovY': subset_df['AccY'].cov(subset_df['AccY']),
            'AccCovZ': subset_df['AccZ'].cov(subset_df['AccZ']),

            'AccSkewX': subset_df['AccX'].skew(),
            'AccSkewY': subset_df['AccY'].skew(),
            'AccSkewZ': subset_df['AccZ'].skew(),

            'AccKurtX': subset_df['AccX'].kurtosis(),
            'AccKurtY': subset_df['AccY'].kurtosis(),
            'AccKurtZ': subset_df['AccZ'].kurtosis(),

            'AccSumX': subset_df['AccX'].sum(),
            'AccSumY': subset_df['AccY'].sum(),
            'AccSumZ': subset_df['AccZ'].sum(),

            'AccMinX': subset_df['AccX'].min(),
            'AccMinY': subset_df['AccY'].min(),
            'AccMinZ': subset_df['AccZ'].min(),

            'AccMaxX': subset_df['AccX'].max(),
            'AccMaxY': subset_df['AccY'].max(),
            'AccMaxZ': subset_df['AccZ'].max(),

            'AccVarX': subset_df['AccX'].var(),
            'AccVarY': subset_df['AccY'].var(),
            'AccVarZ': subset_df['AccZ'].var(),

            'AccMedianX': subset_df['AccX'].median(),
            'AccMedianY': subset_df['AccY'].median(),
            'AccMedianZ': subset_df['AccZ'].median(),

            'AccStdX': subset_df['AccX'].std(),
            'AccStdY': subset_df['AccY'].std(),
            'AccStdZ': subset_df['AccZ'].std(),

            'GyroMeanX': subset_df['GyroX'].mean(),
            'GyroMeanY': subset_df['GyroY'].mean(),
            'GyroMeanZ': subset_df['GyroZ'].mean(),

            'GyroCovX': subset_df['GyroX'].cov(subset_df['GyroX']),
            'GyroCovY': subset_df['GyroY'].cov(subset_df['GyroY']),
            'GyroCovZ': subset_df['GyroZ'].cov(subset_df['GyroZ']),

            'GyroSkewX': subset_df['GyroX'].skew(),
            'GyroSkewY': subset_df['GyroY'].skew(),
            'GyroSkewZ': subset_df['GyroZ'].skew(),

            'GyroKurtX': subset_df['GyroX'].kurtosis(),
            'GyroKurtY': subset_df['GyroY'].kurtosis(),
            'GyroKurtZ': subset_df['GyroZ'].kurtosis(),

            'GyroSumX': subset_df['GyroX'].sum(),
            'GyroSumY': subset_df['GyroY'].sum(),
            'GyroSumZ': subset_df['GyroZ'].sum(),

            'GyroMinX': subset_df['GyroX'].min(),
            'GyroMinY': subset_df['GyroY'].min(),
            'GyroMinZ': subset_df['GyroZ'].min(),

            'GyroMaxX': subset_df['GyroX'].max(),
            'GyroMaxY': subset_df['GyroY'].max(),
            'GyroMaxZ': subset_df['GyroZ'].max(),

            'GyroVarX': subset_df['GyroX'].var(),
            'GyroVarY': subset_df['GyroY'].var(),
            'GyroVarZ': subset_df['GyroZ'].var(),

            'GyroMedianX': subset_df['GyroX'].median(),
            'GyroMedianY': subset_df['GyroY'].median(),
            'GyroMedianZ': subset_df['GyroZ'].median(),

            'GyroStdX': subset_df['GyroX'].std(),
            'GyroStdY': subset_df['GyroY'].std(),
            'GyroStdZ': subset_df['GyroZ'].std(),
        }

        # Apply the model to predict the output
        input_data = np.array(list(statistical_data.values())).reshape(1, -1)
        prediction = model.predict(input_data)[0]

        # Assuming your predictions are numerical labels (1, 2, 3, 4)
        # You can map them to the corresponding actions as before
        predicted_actions = {
            1: 'sudden_acceleration',
            2: 'sudden_right_turn',
            3: 'sudden_left_turn',
            4: 'sudden_break',
            5: 'Normal'
        }

        # Convert numerical prediction to action label
        predicted_action = predicted_actions[prediction]

        # Print or use the predicted action as needed
        print(f'Predicted action: {predicted_action}')

        # Clear the first reading from the data list for the next iteration
        data_list = data_list[1:]
