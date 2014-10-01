import numpy as np
import cv2

capright = cv2.VideoCapture(0)
capleft = cv2.VideoCapture(1)

# Define the codec and create VideoWriter object
#fourcc = cv2.VideoWriter_fourcc(*'XVID')
outLeft = cv2.VideoWriter('outputLeft.avi',-1, 20.0, (640,480))
outRight = cv2.VideoWriter('outputRight.avi',-1, 20.0, (640,480))

frameMax = 120
frameCount = 0
while(frameCount<frameMax):
    if (capright.isOpened()):
        ret, frameRight = capright.read()
        ret, frameLeft = capleft.read()
        if ret==True:
            #frameLeft = cv2.flip(frameLeft,0)
           # frameRight = cv2.flip(frameRight,0)

            # write the flipped frame
            outLeft.write(frameLeft)
            outRight.write(frameRight)
            frameCount = frameCount + 1

# Release everything if job is finished
capright.release()
capleft.release()
outLeft.release()
outRight.release()
cv2.destroyAllWindows()