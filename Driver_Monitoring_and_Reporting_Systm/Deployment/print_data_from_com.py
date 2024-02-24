import serial
import pandas as pd
import matplotlib.pyplot as plt
import time
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

# Read data and store in the list

start_time = time.time()
while True:
    data_values = []  # Create an empty list to store one set of data

    for _ in range(6):  # Read 6 sets of floating-point values
        byte_list = []  # Create a list to store bytes for one floating-point value

        # Read bytes until carriage return '\r' is encountered
        while True:
            data_byte = ser.read(1)
            print(data_byte)
            if data_byte == b'\r':
                break
            byte_list.append(data_byte)

        # Concatenate the bytes and convert to float
        float_value = float(b''.join(byte_list))
        data_values.append(float_value)
        print(data_values)
    # Append the list of data values to data_list
    data_list.append(data_values)
    print(data_list)
    if len(data_list) == 50:  # Check if we have collected 50 sets of data
        # Create a DataFrame using pandas
        end_time = time.time()
        elapsed_time = end_time - start_time
        print(f"Execution time: {elapsed_time} seconds")

        df = pd.DataFrame(data_list, columns=[
                          'GyroX', 'GyroY', 'GyroZ', 'AccX', 'AccY', 'AccZ'])

        # Write DataFrame to Excel file
        df.to_excel('output.xlsx', index=False)
        # Plot each column in a separate subplot
        fig, axs = plt.subplots(3, 2, figsize=(12, 8))
        fig.suptitle('Sensor Data Over Time')

        for i, column in enumerate(df.columns):
            row, col = divmod(i, 2)
            axs[row, col].plot(df.index, df[column], label=column)
            axs[row, col].set_xlabel('Sample')
            axs[row, col].set_ylabel('Value')
            axs[row, col].legend()

        # Adjust layout to prevent clipping of titles
        plt.tight_layout(rect=[0, 0.03, 1, 0.95])

        plt.show()

        data_list = []  # Reset data_list for the next iteration
        break
