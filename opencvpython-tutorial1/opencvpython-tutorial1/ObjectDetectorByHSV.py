import numpy as np
import cv2
from matplotlib import pyplot as plt

capleft = cv2.VideoCapture(1)
lower_t = np.array([160,29,20])
upper_t = np.array([180,255,255])
#lower_t = np.array([110,50,50])
#upper_t = np.array([130,255,255])
kernel = np.ones((3,3),np.uint8)
color = ('b','g','r')
bins = np.arange(256).reshape(256,1)
color = [ (255,0,0),(0,255,0),(0,0,255) ]
numpyZeroArr = np.zeros((300,256,3))
frameCounter = 0;
while(True):
    # Capture frame-by-frame
   # if (capright.isOpened() and capleft.isOpened()):
    ret, frameLeft = capleft.read()

    # Our operations on the frame come here
    #grayRight = cv2.cvtColor(frameRight, cv2.COLOR_BGR2GRAY)
    #grayLeft = cv2.cvtColor(frameLeft, cv2.COLOR_BGR2GRAY)

    hsvl = cv2.cvtColor(frameLeft, cv2.COLOR_BGR2HSV)

    # Threshold the HSV image to get only blue colors
    maskL = cv2.inRange(hsvl, lower_t, upper_t)

    # Bitwise-AND mask and original image
    resL = cv2.bitwise_and(frameLeft,frameLeft, mask= maskL)

    denoisedMaskL = cv2.morphologyEx(maskL, cv2.MORPH_OPEN, kernel)
   # thresholdGaus = cv2.adaptiveThreshold(denoisedMaskL,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY,11,2)

    first,contours, third = cv2.findContours(denoisedMaskL, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    passedContours = []
    for cnt in contours:
        area = cv2.contourArea(cnt)
        print 'area of contour is ' + str(area)
        if area > 500:
              passedContours.append(cnt)
    cv2.drawContours(resL, passedContours, -1, (0,255,0), 3)
  #  cnt = contours[0]
  #  x,y,w,h = cv2.boundingRect(cnt)
  #  cv2.rectangle(resL,(x,y),(x+w,y+h),(0,255,0),2)
    
  # display histogram
    h = numpyZeroArr.copy()
    for ch, col in enumerate(color):
        hist_item = cv2.calcHist([frameLeft],[ch],None,[256],[0,255])
        cv2.normalize(hist_item,hist_item,0,255,cv2.NORM_MINMAX)
        hist=np.int32(np.around(hist_item))
        pts = np.column_stack((bins,hist))
        cv2.polylines(h,[pts],False,col)
        #print "channel: " + str(ch) + " is " + str(h.sum())
    #h=np.flipud(h)

    

    # Display the resulting frame
    cv2.imshow('stream',hsvl)
    cv2.imshow('mask',maskL)
    cv2.imshow('combined',resL)
    cv2.imshow('threshold',denoisedMaskL)
    cv2.imshow('colorhist',h)
    frameCounter = frameCounter + 1
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
capleft.release()
cv2.destroyAllWindows()