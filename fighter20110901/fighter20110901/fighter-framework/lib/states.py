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

capleft = None
capleft = cv2.VideoCapture(0)

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
            print '>>>>>>>>>>>>>>>>>>>>>>>>TRYING TO CAPTURE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<'
            #alpha = ("0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F")
            #randImgName = ''.join([random.choice(alpha) for _ in range(6)])
            renderedSurface = pygame.display.get_surface()
            justTransform(renderedSurface)
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
                print '>>>>>>>>>>>>>>>>>>>>>>>>TRYING TO CAPTURE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<'
                #alpha = ("0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F")
                #randImgName = ''.join([random.choice(alpha) for _ in range(6)])
                renderedSurface = pygame.display.get_surface()
                justTransform(renderedSurface)
                #pygame.image.save(renderedSurface, randImgName + '.jpeg')
                #gfx.update_display()

def transformTheSurface(inputFrame):
    muffinCoords = np.zeros((4,2), np.float32)
    muffinCoords[0] = (0,0)
    muffinCoords[1] = (200,0)
    muffinCoords[2] = (0,200)
    muffinCoords[3] = (200,200)
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
    objp = np.zeros((20,3), np.float32)
    objp[:,:2] = np.mgrid[0:5,0:4].T.reshape(-1,2)
    ret, frameLeft = capleft.read()
    #inputFrameLeft = cv2.cvtColor(inputFrame,cv2.COLOR_BGR2GRAY)
    found, corners = cv2.findChessboardCorners(frameLeft, (5,4),None)
    if (found):
        q = np.zeros((4,2), dtype=np.float32)
        q = corners[[0, 4, 15, 19]]
        npGameFrame = pygame.surfarray.array3d(inputFrame)
        ptMatrix = cv2.getPerspectiveTransform( muffinCoords, q)
        #inputFrameConv = cv2.cvtColor(npGameFrame,cv2.COLOR_BGRA2GRAY)
        transMuffin = cv2.warpPerspective(npGameFrame, ptMatrix, (480, 400)) #, muffinImg, cv2.INTER_NEAREST, cv2.BORDER_CONSTANT,  0)
        cv2.imshow('muffin',transMuffin)
    else:
        print 'cant find corners'



        

def justTransform(inputFrame):
    npGameFrame = pygame.surfarray.array3d(inputFrame)
    pts1 = np.float32([[56,65],[368,52],[28,387],[389,390]])
    pts2 = np.float32([[0,0],[300,0],[0,300],[300,300]])
    ptMatrix = cv2.getPerspectiveTransform( pts1, pts2)
    #inputFrameConv = cv2.cvtColor(npGameFrame,cv2.COLOR_BGRA2GRAY)
    transMuffin = cv2.warpPerspective(npGameFrame, ptMatrix, (480, 400)) #, muffinImg, cv2.INTER_NEAREST, cv2.BORDER_CONSTANT,  0)
    cv2.imshow('muffin',transMuffin)