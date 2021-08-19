#!/usr/bin/env python
import cv2

"""
This is a program that uses cv2 to track a face and
(eventually) shine a laser pointer at it for s&g
"""

KEY_ESC = 0x1b

FRAME_SKIP = 4 # TODO: Implement frame skipping for face detection
DETECT_W = 320
DETECT_H = 240

webcam = cv2.VideoCapture(0)

# Get frame size and print
_, testFrame = webcam.read()
(sourceHeight, sourceWidth) = testFrame.shape[:2]
print("Height: " + str(sourceHeight) + " Width: " + str(sourceWidth))
scaleW = sourceWidth / DETECT_W
scaleH = sourceHeight / DETECT_H

# Use builtin face classifier
faceCascade = cv2.CascadeClassifier('/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml')

def getFacePos(image):
  # Resize and create greyscale image
  grey = cv2.cvtColor(cv2.resize(newFrame, (DETECT_W, DETECT_H)), cv2.COLOR_BGR2GRAY)

  # Find faces (magic)
  faces = faceCascade.detectMultiScale(grey, 1.3, 5)

  # Simple algorithm to find largest face (from https://www.guidodiepen.nl/2017/02/detecting-and-tracking-a-face-with-python-and-opencv/)
  maxArea = 0
  x = 0
  y = 0
  w = 0
  h = 0
  for (_x,_y,_w,_h) in faces:
    if (_w*_h) > maxArea:
      x = _x
      y = _y
      w = _w
      h = _h
      maxArea = w*h
  if maxArea > 0:
    # Return the position of the center of the face (remembering to scale to original image size)
    return (int(x * scaleW + ((w//2)*scaleW)),
            int(y * scaleH + ((h//2)*scaleH)))
  else:
    return (0, 0)


while True:
  # Get frame
  _, newFrame = webcam.read()

  # Draw circle in center of face
  cv2.circle(newFrame, getFacePos(newFrame), 2, (0,255,0), 2)

  # Show frame
  cv2.imshow("Feed", cv2.flip(newFrame, 1))

  # Quit if escape is pressed
  if cv2.waitKey(50) & 0xFF == KEY_ESC:
    break

# Clean up
webcam.release()
cv2.destroyAllWindows()