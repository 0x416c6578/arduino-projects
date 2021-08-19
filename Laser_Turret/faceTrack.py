#!/usr/bin/env python
import cv2

"""
This is a program that uses cv2 to track a face and
(eventually) shine a laser pointer at it for s&g
"""

keyEsc = 0x1b
# TODO: Implement frame skipping for face detection
frameSkip = 4

# Use builtin face classifier
faceCascade = cv2.CascadeClassifier('/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml')

webcam = cv2.VideoCapture(0)

# Get frame size and print
_, oldFrame = webcam.read()
(height, width) = oldFrame.shape[:2]
print("Height: " + str(height) + " Width: " + str(width))

while True:
  _, newFrame = webcam.read()

  # Resize and create greyscale image
  resizedFrame = cv2.resize(newFrame, (320, 240))
  greyFrame = cv2.cvtColor(resizedFrame, cv2.COLOR_BGR2GRAY)

  # Find faces (magic)
  faces = faceCascade.detectMultiScale(greyFrame, 1.3, 5)
  maxArea = 0
  x = 0
  y = 0
  w = 0
  h = 0

  # Simple algorithm to find largest face (from https://www.guidodiepen.nl/2017/02/detecting-and-tracking-a-face-with-python-and-opencv/)
  for (_x,_y,_w,_h) in faces:
    if  _w*_h > maxArea:
      x = _x
      y = _y
      w = _w
      h = _h
      maxArea = w*h
  if maxArea > 0 :
    # Draw dot on center of face
    cv2.rectangle(resizedFrame, 
                  (x+(w//2)-1, y+(h//2)-1),
                  (x+(w//2)+1, y+(h//2)+1),
                  (0,255,0), 2)

  # Show frame
  cv2.imshow("Feed", cv2.resize(cv2.flip(resizedFrame, 1), (640, 480)))

  # Quit if escape is pressed
  if cv2.waitKey(100) & 0xFF == keyEsc:
    break

# Clean up
webcam.release()
cv2.destroyAllWindows()