import numpy as np
import cv2

capright = cv2.VideoCapture(0)

# Define the codec and create VideoWriter object
#fourcc = cv2.VideoWriter_fourcc(*'XVID')

frameMax = 180
frameWait = 60
frameCount = 0
while(frameCount<frameMax):
    if frameCount >= frameWait:
        if (capright.isOpened()):
            ret, frameRight = capright.read()
            if ret==True:
                #frameLeft = cv2.flip(frameLeft,0)
               # frameRight = cv2.flip(frameRight,0)

                # write the flipped frame
                cv2.imwrite('image' + str(frameCount) + '.png',frameRight)
                frameCount = frameCount + 1

# Release everything if job is finished
capright.release()
capleft.release()
outLeft.release()
outRight.release()
cv2.destroyAllWindows()