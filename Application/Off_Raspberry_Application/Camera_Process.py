import queue
import time
import picamera

# Initialize the queues
traffic_process_queue = queue.Queue()
lane_process_queue = queue.Queue()

# Setup Pi Camera
camera = picamera.PiCamera()

# Function to capture and distribute images
def camera_service_process():
    try:
        camera.resolution = (1024, 768)
        while True:
            # Capture image
            stream = io.BytesIO()
            camera.capture(stream, format='jpeg')
            
            # Move to the beginning of the stream
            stream.seek(0)
            
            # Read image data
            image_data = stream.read()
            
            # Put the image data in both queues
            traffic_process_queue.put(image_data)
            lane_process_queue.put(image_data)
            
            # Sleep for a specified interval before capturing next image
            time.sleep(1)
            
    except Exception as e:
        print(f"Error in camera service process: {e}")
    finally:
        camera.close()

if __name__ == "__main__":
    camera_service_process()
