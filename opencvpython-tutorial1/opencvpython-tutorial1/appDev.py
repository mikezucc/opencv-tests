import numpy as np
import cv2
import glob

def cameraCalib():
    # termination criteria
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

    # prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
    objp = np.zeros((3*3,3), np.float32)
    objp[:,:2] = np.mgrid[0:3,0:3].T.reshape(-1,2)

    # Arrays to store object points and image points from all the images.
    objpoints = [] # 3d point in real world space
    imgpoints = [] # 2d points in image plane.

    images = glob.glob('./recorded/*.png')

    meanErrList = []
    matrixList = []

    for fname in images:
        img = cv2.imread(fname)
        gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

        # Find the chess board corners
        ret, corners = cv2.findChessboardCorners(gray, (3,3),None)

        # If found, add object points, image points (after refining them)
        if ret == True:
            objpoints.append(objp)

            cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
            imgpoints.append(corners)

            # Draw and display the corners
            cv2.drawChessboardCorners(img, (3,3), corners,ret)
            cv2.imshow('img',img)

            ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1],None,None)

            mean_error = 0
            tot_error = 0
            for i in xrange(len(objpoints)):
                imgpoints2, _ = cv2.projectPoints(objpoints[i], rvecs[i], tvecs[i], mtx, dist)
                error = cv2.norm(imgpoints[i],imgpoints2, cv2.NORM_L2)/len(imgpoints2)
                tot_error += error

            mean_error = tot_error/(len(xrange(len(objpoints))))
            print "total error: ", mean_error/len(objpoints)

            meanErrList.append(mean_error)
            matrixList.append([ret, mtx, dist, rvecs, tvecs])

            cv2.waitKey(1000)

    minErrIdx = meanErrList.index(min(meanErrList))
    selCalibData = matrixList[minErrIdx]
    print selCalibData
    np.savez("calibData.npz",selCalibData)


def ARShowAxes():
    capleft = cv2.VideoCapture(1)
    ret, frameLeft = capleft.read()
    width, height = frameLeft.shape[:2]
    adjH = width/2
    adjL = height/2
    while (1):
        ret, frameLeft = capleft.read()
        frame = frameLeft.copy()
        
        found, corners = cv2.findChessboardCorners(frameLeft, (3,3))

        if (found):
            q = [(0,0)]*4
            e = [(0,0)]*4

            q[0] = corners[0]
            q[1] = corners[2]
            q[2] = corners[8]
            q[3] = corners[6]
            something = q[0][0]
            print str(something)
            cv2.line(frameLeft, (q[0][0][0],q[0][0][1]) , (q[1][0][0], q[1][0][1]) , (255,0,0),2)
            cv2.line(frameLeft, (q[1][0][0],q[1][0][1]) , (q[2][0][0], q[2][0][1]) , (255,255,0),2)
            cv2.line(frameLeft, (q[2][0][0],q[2][0][1]) , (q[3][0][0], q[3][0][1]) , (255,0,255),2)
            cv2.line(frameLeft, (q[3][0][0],q[3][0][1]) , (q[0][0][0], q[0][0][1]) , (0,0,255),2)


            #cv2.line(frameLeft, q[1][0] , q[2][0] , (255,255,0),2)
           # cv2.line(frameLeft, q[2][0] , q[3][0] , (255,0,255),2)
            #cv2.line(frameLeft, q[3][0] , q[0][0] , (0,0,255),2)
             
        cv2.imshow('stream',frameLeft)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break


cameraCalib()