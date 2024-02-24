import numpy as np
import pandas as pd
import pickle

# Load your original Excel sheet as a Pandas DataFrame
# Replace with the path to your original Excel file
excel_file = r'output.xlsx'
df = pd.read_excel(excel_file)
# df['AccZ'] = df['AccZ']*-1
df['AccX'] = df['AccX'] / (1.15)
df['AccY'] = df['AccY'] / (1.15)
df['AccZ'] = df['AccZ'] / (1.15)
df['GyroX'] = df['GyroX'] / (1.15)
df['GyroY'] = df['GyroY'] / (1.15)
df['GyroZ'] = df['GyroZ'] / (1.15)

# Create a new DataFrame for statistical calculations
columns = [
    'AccMeanX', 'AccMeanY', 'AccMeanZ',
    'AccCovX', 'AccCovY', 'AccCovZ',
    'AccSkewX', 'AccSkewY', 'AccSkewZ',
    'AccKurtX', 'AccKurtY', 'AccKurtZ',
    'AccSumX', 'AccSumY', 'AccSumZ',
    'AccMinX', 'AccMinY', 'AccMinZ',
    'AccMaxX', 'AccMaxY', 'AccMaxZ',
    'AccVarX', 'AccVarY', 'AccVarZ',
    'AccMedianX', 'AccMedianY', 'AccMedianZ',
    'AccStdX', 'AccStdY', 'AccStdZ',
    'GyroMeanX', 'GyroMeanY', 'GyroMeanZ',
    'GyroCovX', 'GyroCovY', 'GyroCovZ',
    'GyroSkewX', 'GyroSkewY', 'GyroSkewZ',
    'GyroKurtX', 'GyroKurtY', 'GyroKurtZ',
    'GyroSumX', 'GyroSumY', 'GyroSumZ',
    'GyroMinX', 'GyroMinY', 'GyroMinZ',
    'GyroMaxX', 'GyroMaxY', 'GyroMaxZ',
    'GyroVarX', 'GyroVarY', 'GyroVarZ',
    'GyroMedianX', 'GyroMedianY', 'GyroMedianZ',
    'GyroStdX', 'GyroStdY', 'GyroStdZ',
]

stat_df = pd.DataFrame(columns=columns)

# Calculate statistical measures for varying window sizes
for window_size in range(4, 15):
    # for i in range(0, len(df) - window_size + 1):
    # Select rows based on window size
    subset_df = df.iloc[0:window_size]
    stat_df.loc[len(stat_df)] = {
        # 'Target': subset_df['Target'].max(),
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

for i in range(1, len(df) - 7):  # 1 to 1
    # Select rows based on window size
    subset_df = df.iloc[i:i+8]
    stat_df.loc[len(stat_df)] = {
        # 'Target': subset_df['Target'].max(),
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
# Save the new DataFrame with statistical calculations to a new Excel file
stat_excel_file = 'statistical_data.xlsx'
stat_df.to_excel(stat_excel_file, index=False)
print(f'Statistical data saved to {stat_excel_file}')

# Load your exported model
with open(r'mobile\final\mobile_2_model_2_with.pkl', 'rb') as file:
    model = pickle.load(file)

# Load your Excel sheet into a Pandas DataFrame
excel_file_path = 'statistical_data.xlsx'
df2 = pd.read_excel(excel_file_path)


probabilities = model.predict_proba(df2)

# Assuming your predictions are numerical labels (1, 2, 3, 4)
# You can map them to the corresponding actions as before
predicted_actions = {
    1: 'sudden_acceleration',
    2: 'sudden_right_turn',
    3: 'sudden_left_turn',
    4: 'sudden_break',
    5: 'Normal'
}

# Convert numerical predictions to action labels
df2['predicted_action'] = [predicted_actions[prediction.argmax() + 1]
                           for prediction in probabilities]

# Add the probability of the predicted action to the DataFrame
df2['probability_predicted_action'] = [prediction[prediction.argmax()]
                                       for prediction in probabilities]

# Save the DataFrame with predictions and probabilities to a new Excel file if needed
df2.to_excel('output_predictions_with_probabilities.xlsx', index=False)
