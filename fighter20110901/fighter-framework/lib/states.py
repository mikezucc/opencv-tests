"""
Copyright 2009, 2010, 2011 Leif Theden

This file is part of Fighter Framework.

Fighter Framework (FF) is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

FF is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with FF.  If not, see <http://www.gnu.org/licenses/>.
"""

import pygame
from pygame.locals import *
from collections import deque

import random
import numpy as np
import cv2
import glob
import threading
import time

capleft = None
capleft = cv2.VideoCapture(0)
cv2.namedWindow('muffin', cv2.WINDOW_AUTOSIZE)

muffinCoords = np.zeros((4,2), np.float32)
muffinCoords[0] = (200,200)
muffinCoords[1] = (400,200)
muffinCoords[2] = (200,400)
muffinCoords[3] = (400,400)

muffinIll = np.zeros((3,2), np.float32)
muffinIll[0] = (200,200)
muffinIll[1] = (400,200)
muffinIll[2] = (300,400)

criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
objp = np.zeros((20,3), np.float32)
objp[:,:2] = np.mgrid[0:5,0:4].T.reshape(-1,2)
axis = np.float32([[3,0,0], [0,3,0], [0,0,-3]]).reshape(-1,3)
q = np.zeros((4,2), dtype=np.float32)
isDisplayed = False

#load calib data
loadedCalibFileMTX = np.load('calibDataMTX.npy')
loadedCalibFileDIST = np.load('calibDataDIST.npy')
print loadedCalibFileMTX
print loadedCalibFileDIST
mtx = loadedCalibFileMTX
dist = loadedCalibFileDIST[0]

class GameState(object):
    def __init__(self, driver):
        self._driver = driver
        self.activated = False

    def activate(self):
        self.activated = True

    def reactivate(self):
        pass

    def deactivate(self):
        pass

    def draw(self, surface):
        pass

    def key_event(self, key, unicode, pressed):
        pass

    def mask_event(self, key, unicode, pressed):
        self.key_event(key, unicode, pressed)

    def update(self, time):
        pass

class StateDriver(object):
    def __init__(self, parent):
        self.parent = parent
        self._states = deque()
        self.reloadScreen()

    def reloadScreen(self):
        """ Called when the display changes mode somehow. """
        self._screen = self.parent.get_screen()

    def done(self):
        self.getCurrentState().deactivate()
        self._states.pop()
        state = self.getCurrentState()
        if state.activated:
            state.reactivate()
        else:
            state.activate()

    def getCurrentState(self):
        try:
            return self._states[-1]
        except:
            self.quit()

    def get_size(self):
        return self._screen.get_size()

    def get_screen(self):
        return self._screen

    def quit(self):
        pygame.quit()

    def replace(self, state):
        self.getCurrentState().deactivate()
        self._states.pop()
        self.start(state)

    def start(self, state):
        self._states.append(state)
        self.getCurrentState().activate()

    def push(self, state):
        self._states.appendleft(state)

    def run(self):
        currentState = self.getCurrentState()
        import lib.gfx as gfx

        # deref for speed
        event_poll = pygame.event.poll
        event_pump = pygame.event.pump
        wait       = pygame.time.wait
        get_ticks  = pygame.time.get_ticks
        current_state = self.getCurrentState
        
        clock = pygame.time.Clock()

        while currentState:
            if not isDisplayed:
                renderedSurface = pygame.display.get_surface()
                threadPerspectiveRenderNew = threadPerspectiveRender(1, renderedSurface)
                threadPerspectiveRenderNew.start()
                #justTransform(renderedSurface)
                #pygame.image.save(renderedSurface, randImgName + '.jpeg')
                #gfx.update_display()
            clock.tick(40)

            event = event_poll()

            while event.type != NOEVENT:
                if event.type == QUIT:
                    currentState = None
                    break
                elif event.type == KEYUP or event.type == KEYDOWN:
                    if event.key == K_ESCAPE:
                        currentState = None
                        break
                    if event.type == KEYUP:
                        currentState.mask_event(event.key, None, False)
                    if event.type == KEYDOWN:
                        currentState.mask_event(event.key, event.unicode, True)

                event = event_poll()

            if currentState:
                currentState.update(30)
                currentState.draw(self._screen)
                currentState = current_state()
                gfx.update_display()

def transformTheSurface(inputFrame):
    ret, frameLeft = capleft.read()
    capGray = cv2.cvtColor(frameLeft,cv2.COLOR_BGR2GRAY)
    found, corners = cv2.findChessboardCorners(capGray, (5,4), None, cv2.CALIB_CB_NORMALIZE_IMAGE + cv2.CALIB_CB_ADAPTIVE_THRESH ) #,None,cv2.CALIB_CB_FAST_CHECK)
    if (found):
        npGameFrame = pygame.surfarray.array3d(inputFrame)
        inputFrameGray = cv2.cvtColor(npGameFrame,cv2.COLOR_BGR2GRAY)
        #corners2 = cv2.cornerSubPix(inputFrameGray,corners,(7,7),(-1,-1),criteria)
        cv2.drawChessboardCorners(frameLeft, (5,4), corners, found)
        q = corners[[0, 4, 15, 19]]
        ptMatrix = cv2.getPerspectiveTransform( muffinCoords, q)
        
        ptMatrixflip = np.flipud(ptMatrix)
        npGameFrame = cv2.flip(npGameFrame, 0)

        # derive own rotation matrix
        #XRotMat = np.matrix([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
        xRotVect = np.array([1, 0, 0], dtype=np.float)
        xRotMatRod = cv2.Rodrigues(xRotVect)
        print ptMatrix
        ptMatrixWithXRot = ptMatrix.dot(xRotMatRod)
        #inputFrameConv = cv2.cvtColor(npGameFrame,cv2.COLOR_BGRA2GRAY)
        transMuffin = cv2.warpPerspective(npGameFrame, ptMatrixWithXRot, (640, 480)) #, muffinImg, cv2.INTER_NEAREST, cv2.BORDER_CONSTANT,  0)

        #ret, rvecs, tvecs = cv2.solvePnP(objp, corners2, mtx, dist)
        #rodRotMat = cv2.Rodrigues(rvecs)
        #print 'new mat'
        #print rodRotMat
        # I want to put logo on top-left corner, So I create a ROI
        rows,cols,channels = transMuffin.shape
        roi = frameLeft[0:rows, 0:cols]

        # Now create a mask of logo and create its inverse mask also
        transMuffingray = cv2.cvtColor(transMuffin,cv2.COLOR_BGR2GRAY)
        ret, mask = cv2.threshold(transMuffingray, 10, 255, cv2.THRESH_BINARY)
        mask_inv = cv2.bitwise_not(mask)

        # Now black-out the area of logo in ROI
        frameLeft_bg = cv2.bitwise_and(roi,roi,mask = mask_inv)

        # Take only region of logo from logo image.
        transMuffin_fg = cv2.bitwise_and(transMuffin,transMuffin,mask = mask)

        # Put logo in ROI and modify the main image
        dst = cv2.add(frameLeft_bg,transMuffin_fg)
        frameLeft[0:rows, 0:cols ] = dst
        frameLeft = cv2.cvtColor(frameLeft,cv2.COLOR_RGB2BGR)
        cv2.imshow('muffin',frameLeft)
    else:
        print 'cant find corners'

class threadPerspectiveRender (threading.Thread):
    def __init__(self, threadID, inputFrame):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.inputFrame = inputFrame
    def run(self):
        transformTheSurface(self.inputFrame)
        isDisplayed = True
        
def justTransform(inputFrame):
    print 'just transform'
    npGameFrame = pygame.surfarray.array3d(inputFrame)
    pts1 = np.float32([[56,65],[368,52],[28,387],[389,390]])
    pts2 = np.float32([[0,0],[300,0],[0,300],[300,300]])
    ptMatrix = cv2.getPerspectiveTransform( pts1, pts2)
    #inputFrameConv = cv2.cvtColor(npGameFrame,cv2.COLOR_BGRA2GRAY)
    transMuffin = cv2.warpPerspective(npGameFrame, ptMatrix, (480, 400)) #, muffinImg, cv2.INTER_NEAREST, cv2.BORDER_CONSTANT,  0)
    cv2.imshow('muffin',transMuffin)