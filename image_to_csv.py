import cv2
import csv

image = cv2.imread('cat.png', cv2.IMREAD_GRAYSCALE)

edges = cv2.Canny(image, 50, 450)

contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

epsilon_factor = 0.0001

with open('line_segments.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["x1", "y1", "x2", "y2"])

    for contour in contours:
        epsilon = epsilon_factor * cv2.arcLength(contour, True)
        approx_curve = cv2.approxPolyDP(contour, epsilon, True)

        for i in range(len(approx_curve) - 1):
            x1, y1 = approx_curve[i][0]
            x2, y2 = approx_curve[i + 1][0]
            writer.writerow([x1, y1, x2, y2])
