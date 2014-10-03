import numpy as np
import cv2
from matplotlib import pyplot as plt

def saveAFrameToPNG(frameCounter, resL):
    cv2.imwrite('./recorded/pic' + str(frameCounter) + '.png',resL)

def promptAndDetectByColor():
    capleft = cv2.VideoCapture(1)
    ret, frameLeft = capleft.read()
    width, height = frameLeft.shape[:2]
    adjH = width/2
    adjL = height/2
    while (1):
        ret, frameLeft = capleft.read()
        frame = frameLeft.copy()
        cv2.circle(frameLeft,(adjL,adjH), 30, (0,0,255), 5)
        cv2.imshow('stream',frameLeft)
        if cv2.waitKey(1) & 0xFF == ord('c'):
            break

    #capleft.release()
    #cv2.destroyAllWindows()
    # mask out the selected image area
    frameHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    lower_t = np.array([150,1,1])
    upper_t = np.array([180,2,2])
    #blackImageMat = np.zeros((height,width,3))
    maskL = cv2.inRange(frameHSV, lower_t, upper_t)
    cv2.circle(maskL,(adjL,adjH), 30, (255,255,255), -1)
    cv2.imshow('selectedmaskL',maskL)
    while not (cv2.waitKey(1) & 0xFF == ord('q')):
        print "waiting"
    #cv2.imshow('blackImageMat',blackImageMat)
    resL = cv2.bitwise_and(frame,frame,mask= maskL)
    cv2.imshow('resL',resL)
    while not (cv2.waitKey(1) & 0xFF == ord('q')):
        print "waiting"
    cv2.destroyAllWindows()
print "here"
promptAndDetectByColor()