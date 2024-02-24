# import torch
# from pathlib import Path
# from PIL import Image
# import matplotlib.pyplot as plt

# # Load YOLOv8 model
# # Replace with the actual path to your yolov8.pt file
# model_path = "yolov8n.pt"
# model = torch.hub.load('ultralytics/yolov5:v5.0', 'custom', path=model_path)

# # Load the image
# # Replace with the actual path to your image
# image_path = "CF6680.jpg"
# img = Image.open(image_path)

# # Make predictions
# results = model(img)

# # Display the results
# results.show()

# # Save the results
# results.save(Path("output"))

# # You can also access the prediction data
# predictions = results.xyxy[0].numpy()
# print(predictions)

from ultralytics import YOLO
from ultralytics.models.yolo.detect import DetectionPredictor
import cv2
model = YOLO("best.pt")
model.predict(
    source="Free_Printable_Number_Bubble_Letters_Bubble_Number_80.jpg", show=True, conf=0.5)
