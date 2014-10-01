import numpy as np
import cv2

capright = cv2.VideoCapture(0)
capleft = cv2.VideoCapture(1)
while(True):
    # Capture frame-by-frame
   # if (capright.isOpened() and capleft.isOpened()):
    ret, frameRight = capright.read()
    ret, frameLeft = capleft.read()
   # else:
   #     if capright.isOpened():
   #         capleft.open()
   #     if capleft.isOpened():
    #        capright.open()
    #    ret, frameRight = capright.read()
   #     ret, frameLeft = capleft.read()
    # Our operations on the frame come here
    grayRight = cv2.cvtColor(frameRight, cv2.COLOR_BGR2GRAY)
    grayLeft = cv2.cvtColor(frameLeft, cv2.COLOR_BGR2GRAY)

    cv2.namedWindow('rightWindow', 1)
    cv2.namedWindow('leftWindow', 1)

    # Display the resulting frame
    cv2.imshow('rightWindow',grayRight)
    cv2.imshow('leftWindow',grayLeft)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
capright.release()
capleft.release()
cv2.destroyAllWindows()