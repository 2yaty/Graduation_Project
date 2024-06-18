import requests

def send_shared_trip_data(shared_trip):
    # API endpoint URL
    url = "https://dmrs-c487bb5f6150.herokuapp.com/api/v1/trips"

    serial_number = "12345678910"

    # API key for authentication
    api_key = "e9H3pMSRS7Bxd1XXCUVPVCIT0ntESkjEB0h0JNqyW2tDu6rLW0i48EJxQFQZkRMfDrTuy9lBivLJmQ54Bjo6sDEeAsWIGafszZE1MEID1OIXkMXHyJOH6m7CHuYFCq3o"


    # Prepare the headers with the API key
    headers = {
        "CAR-API-KEY": api_key
    }

    shared_trip["serialNumber"] = serial_number

    try:
        # Send the POST request to the API endpoint with headers
        response = requests.post(url, json=shared_trip, headers=headers)

        # Check the response status code
        if response.status_code == 200:
            print("Shared trip data sent successfully!")
        else:
            print("Failed to send shared trip data. Status code:", response.status_code)

    except requests.exceptions.RequestException as e:
        print("An error occurred while sending shared trip data:", str(e))

# Example usage
shared_trip_data = {
    "start_time": "2023-12-24T05:22:55",
            "end_time": "2023-12-24T06:00:55",
            "suddenBraking": 100,
            "suddenAcceleration": 8,
            "aggTL": 11,
            "aggTR": 14,
            "speedLimitViolation": 17,
            "normalDriving": 20,
            "totalScore": 70
}

send_shared_trip_data(shared_trip_data)