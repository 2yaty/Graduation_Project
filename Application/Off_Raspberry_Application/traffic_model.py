# traffic_app.py
from ultralytics import YOLO
from ultralytics.models.yolo.detect import DetectionPredictor
import cv2


def predict_traffic_sign(image):

    model = YOLO(
        r"/home/pi/Desktop/Final_application/Graduation_Project/Application/Off_Raspberry_Application/traffic_best.pt")
    return model.predict(source=image, show=True, conf=0.5)
