"""
Messing about with the libfreenect pythonw wrapper
"""

import freenect
import time
import cv2

image = 0

KEY_ESC = 0x1b

ctx = freenect.init()
dev = freenect.open_device(ctx, 0)

freenect.set_tilt_degs(dev, -20)
time.sleep(3)
freenect.set_tilt_degs(dev, 20)
time.sleep(3)
freenect.set_tilt_degs(dev, 0)
time.sleep(3)

def imageCallback(dev, imageData, timestamp):
  return

def depthCallback(dev, depthData, timestamp):
  global image
  image = depthData
  return

def bodyCallback(dev, ctx):
  cv2.imshow("Feed", cv2.flip(image, 1))

freenect.runloop(depth=depthCallback, video=imageCallback, body=bodyCallback, dev=dev)

# freenect.stop_video(dev)
# 
# freenect.close_device(dev)
# freenect.shutdown(ctx)
