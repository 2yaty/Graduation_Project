import requests

def send_shared_trip_data(shared_trip):
    # API endpoint URL
    url = "https://api.example.com/send_shared_trip_data"

    serial_number = "your_serial_number_here"

    # API key for authentication
    api_key = "your_api_key_here"


    # Prepare the headers with the API key
    headers = {
        "Authorization": f"Bearer {api_key}",
        "serial_number": serial_number  
    }

    try:
        # Send the POST request to the API endpoint with headers
        response = requests.post(url, json=shared_trip.get_trip_statistics(), headers=headers)

        # TODO: send the response state to the STM
        # Check the response status code
        if response.status_code == 200:
            print("Shared trip data sent successfully!")
        else:
            print("Failed to send shared trip data. Status code:", response.status_code)

    except requests.exceptions.RequestException as e:
        print("An error occurred while sending shared trip data:", str(e))

# Example usage
shared_trip_data = {
    "trip_id": 12345,
    "start_location": "New York",
    "end_location": "San Francisco",
    # Add more shared trip data fields as needed
}

send_shared_trip_data(shared_trip_data)