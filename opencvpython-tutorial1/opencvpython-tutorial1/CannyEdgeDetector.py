import numpy as np
import cv2

capright = cv2.VideoCapture(0)
capleft = cv2.VideoCapture(1)
cv2.namedWindow('streamright', 1)
cv2.namedWindow('streamleft', 1)
cv2.namedWindow('cannystreamleft', 1)
cv2.namedWindow('cannystreamright', 1)
while(True):
    # Capture frame-by-frame
   # if (capright.isOpened() and capleft.isOpened()):
    ret, frameRight = capright.read()
    ret, frameLeft = capleft.read()

    # Our operations on the frame come here
    grayRight = cv2.cvtColor(frameRight, cv2.COLOR_BGR2GRAY)
    grayLeft = cv2.cvtColor(frameLeft, cv2.COLOR_BGR2GRAY)

    edgesLeft = cv2.Canny(grayRight,100,200)
    edgesRight = cv2.Canny(grayLeft,100,200)    

    # Display the resulting frame
    cv2.imshow('streamright',grayRight)
    cv2.imshow('streamleft',grayLeft)
    cv2.imshow('cannystreamright',edgesRight)
    cv2.imshow('cannystreamleft',edgesLeft)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
capright.release()
capleft.release()
cv2.destroyAllWindows()