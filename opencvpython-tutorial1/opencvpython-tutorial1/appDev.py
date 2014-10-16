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
            matrixList.append([mtx, dist, rvecs, tvecs])

            #cv2.waitKey(100)

    minErrIdx = meanErrList.index(min(meanErrList))
    selCalibData = matrixList[minErrIdx]
    #print selCalibData
    np.save("calibDataMTX",selCalibData[0])
    np.save("calibDataDIST",selCalibData[1])
    np.save("calibDataRVECS",selCalibData[2])
    np.save("calibDataTVECS",selCalibData[3])
    loadedCalibFileMTX = np.load('calibDataMTX.npy')
    loadedCalibFileDIST = np.load('calibDataDIST.npy')
    loadedCalibFileRVECS = np.load('calibDataRVECS.npy')
    loadedCalibFileTVECS = np.load('calibDataTVECS.npy')
    print loadedCalibFileMTX
    print loadedCalibFileDIST
    print loadedCalibFileRVECS
    print loadedCalibFileTVECS
    mtx = loadedCalibFileMTX[0]
    dist = loadedCalibFileDIST[0]
    rvecs = loadedCalibFileRVECS[0]
    tvecs = loadedCalibFileTVECS[0]
    print mtx
    print dist
    print rvecs
    print tvecs

def ARShowAxes():
    capleft = cv2.VideoCapture(0)
    ret, frameLeft = capleft.read()
    width, height = frameLeft.shape[:2]
    adjH = width/2
    adjL = height/2

    muffinImg = cv2.imread('muffin.jpg',0)
    muffinCoords = np.zeros((4,2), np.float32)
    muffheight, muffwidth = muffinImg.shape
    muffinCoords[0] = (0,muffwidth)
    muffinCoords[1] = (muffwidth,muffheight)
    muffinCoords[2] = (0,muffheight)
    muffinCoords[3] = (0,0)

    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
    objp = np.zeros((20,3), np.float32)
    objp[:,:2] = np.mgrid[0:5,0:4].T.reshape(-1,2)

    axis = np.float32([[3,0,0], [0,3,0], [0,0,-3]]).reshape(-1,3)

    #load calib data
    loadedCalibFileMTX = np.load('calibDataMTX.npy')
    loadedCalibFileDIST = np.load('calibDataDIST.npy')
    loadedCalibFileRVECS = np.load('calibDataRVECS.npy')
    loadedCalibFileTVECS = np.load('calibDataTVECS.npy')
    print loadedCalibFileMTX
    print loadedCalibFileDIST
    print loadedCalibFileRVECS
    print loadedCalibFileTVECS
    mtx = loadedCalibFileMTX
    dist = loadedCalibFileDIST[0]
    rvecsLoaded = loadedCalibFileRVECS[0]
    tvecsLoaded = loadedCalibFileTVECS[0]


    while (1):
        ret, frameLeft = capleft.read()
        # frame = frameLeft.copy()
        
        grayframeLeft = cv2.cvtColor(frameLeft,cv2.COLOR_BGR2GRAY)
        found, corners = cv2.findChessboardCorners(frameLeft, (5,4),None)

        if (found):
            corners2 = cv2.cornerSubPix(grayframeLeft,corners,(11,11),(-1,-1),criteria)
            #rvecs, tvecs, inliers = cv2.solvePnPRansac(objp, corners2, loadedCalibFileMTX, loadedCalibFileDIST)
            ret, rvecs, tvecs = cv2.solvePnP(objp, corners2, mtx, dist, rvecsLoaded, tvecsLoaded, 0,cv2.ITERATIVE )
            #transfMat = cv2.getPerspectiveTransform(objp, corners2)
            
            q = np.zeros((4,2), dtype=np.float32)
            q = corners[[0, 3, 19, 16]]
           # q[0] = corners[0][0]
           # q[1] = corners[3][0]
          #  q[2] = corners[19][0]
           # q[3] = corners[16][0]

            retvalHomography, mask = cv2.findHomography(q, muffinCoords, cv2.RANSAC)
            cv2.warpPerspective(muffinImg, retvalHomography, (400, 500), muffinImg, cv2.INTER_NEAREST, cv2.BORDER_CONSTANT,  0)
            # project 3D points to image plane
            print "new entry \n"
            print "rvecs: "
            print rvecs
            print "tvecs: "
            print tvecs
            imgpts, jac = cv2.projectPoints(axis, rvecs, tvecs, loadedCalibFileMTX, loadedCalibFileDIST)
            print "\nimage points: "
            print imgpts
            corner = tuple(corners2[0].ravel())
            try:
                cv2.line(frameLeft, corner, tuple(imgpts[0].ravel()), (255,0,0), 5)
                cv2.line(frameLeft, corner, tuple(imgpts[1].ravel()), (0,255,0), 5)
                cv2.line(frameLeft, corner, tuple(imgpts[2].ravel()), (0,0,255), 5)

                imgpts = np.int32(imgpts).reshape(-1,2)
                # draw ground floor in green
                frameLeft = cv2.drawContours(frameLeft, [imgpts[:4]],-1,(0,255,0),-3)

                # draw pillars in blue color
                for i,j in zip(range(4),range(4,8)):
                    img = cv2.line(frameLeft, tuple(imgpts[i]), tuple(imgpts[j]),(255),3)

                # draw top layer in red color
                img = cv2.drawContours(frameLeft, [imgpts[4:]],-1,(0,0,255),3)
            except:
                print "lost tracking"
            q = [(0,0)]*4
            e = [(0,0)]*4

            q[0] = corners[0]
            q[1] = corners[2]
            q[2] = corners[8]
            q[3] = corners[6]
            something = q[0][0]
            #print str(something)
            cv2.line(frameLeft, (q[0][0][0],q[0][0][1]) , (q[1][0][0], q[1][0][1]) , (255,0,0),2)
            cv2.line(frameLeft, (q[1][0][0],q[1][0][1]) , (q[2][0][0], q[2][0][1]) , (255,255,0),2)
            cv2.line(frameLeft, (q[2][0][0],q[2][0][1]) , (q[3][0][0], q[3][0][1]) , (255,0,255),2)
            cv2.line(frameLeft, (q[3][0][0],q[3][0][1]) , (q[0][0][0], q[0][0][1]) , (0,0,255),2)


            #cv2.line(frameLeft, q[1][0] , q[2][0] , (255,255,0),2)
           # cv2.line(frameLeft, q[2][0] , q[3][0] , (255,0,255),2)
            #cv2.line(frameLeft, q[3][0] , q[0][0] , (0,0,255),2)
             
        cv2.imshow('stream',frameLeft)
        cv2.imshow('muffin',muffinImg)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break


ARShowAxes()