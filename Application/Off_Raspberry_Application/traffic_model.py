# traffic_app.py
from ultralytics import YOLO
from ultralytics.models.yolo.detect import DetectionPredictor
import cv2


def predict_traffic_sign(image):

    model = YOLO(
        r".\traffic_best.pt")
    return model.predict(source=image, show=False, conf=0.5)
