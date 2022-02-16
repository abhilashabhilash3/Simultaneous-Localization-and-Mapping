import numpy as np
import cv2
import time
import math
import serial
import sys
import string

global intx
global inty

height    = 400
width     = 400
margin    = 20
divisions = 9
box       = ( width - ( margin * 2 )) / divisions
intx      = margin
inty      = height - margin
flag      = 0
robotmargin = 30
frontswitch = 0
openswitch  = 0
sensorL = 0
sensorF = 0
sensorR = 0
count   = 0
flag1 = 0
count1 = 0

global ser

def serialBegin():
    global ser
    ser = serial.Serial(2,9600)
    time.sleep(10)

def serialClose():
    global ser
    ser.close()
    
def serialwrite(content):
    global ser
    ser.write(content)

def serialRead():
    global ser
    count = 0
    while True:
        ser.timeout = 1
        val = ser.readline()
        print val
        if val != '':
            x = string.replace(val,'\r\n','')
            if x == 'F':
                returnvalue = 'F'
            elif x == 'L':
                returnvalue = 'L'
            elif x == 'R':
                returnvalue = 'R'
            else:
                try:
                    returnvalue = int(string.replace(val,'\r\n',''))
                except:
                    returnvalue = 999
            break
        else:
            count = count + 1
        if count > 10:
            ser.write('S')
    return returnvalue

def drawfront( x, y ):
    global box
    global robotmargin
    cv2.circle(img,((x+int(box/2)),(y-int(box/5))),2,(0,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*2))),2,(0,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*3))),2,(0,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*4))),2,(0,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*5))),2,(0,0,0),-1)
    
    cv2.circle(img,((x+int(box/2)),(y-int(box/5))),2,(150,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*2))),2,(150,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*3))),2,(150,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*4))),2,(150,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*5))),2,(150,0,0),-1)

def drawleft( x, y ):
    global box
    global robotmargin
    cv2.circle(img,((x+int(box/2)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*2)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*3)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*4)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*5)),(y-int(box/2))),2,(0,0,0),-1)
    
    cv2.circle(img,((x+int(box/2)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*2)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*3)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*4)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*5)),(y-int(box/2))),2,(150,0,0),-1)

def drawright( x, y ):
    global box
    global robotmargin
    cv2.circle(img,((x+int(box/2)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*2)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*3)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*4)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*5)),(y-int(box/2))),2,(0,0,0),-1)
    
    cv2.circle(img,((x+int(box/2)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*2)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*3)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*4)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*5)),(y-int(box/2))),2,(150,0,0),-1)

def drawback( x, y ):
    global box
    global robotmargin
    cv2.circle(img,((x+int(box/2)),(y-int(box/5))),2,(0,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*2))),2,(0,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*3))),2,(0,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*4))),2,(0,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*5))),2,(0,0,0),-1)
    
    cv2.circle(img,((x+int(box/2)),(y-int(box/5))),2,(150,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*2))),2,(150,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*3))),2,(150,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*4))),2,(150,0,0),-1)
    cv2.circle(img,((x+int(box/2)),(y-(int(box/5)*5))),2,(150,0,0),-1)

def drawrightfront( x, y ):
    global box
    global robotmargin
    cv2.circle(img,((x+int(box/2)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*2)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*3)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*4)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*5)),(y-int(box/2))),2,(0,0,0),-1)
    
    cv2.circle(img,((x+int(box/2)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*2)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*3)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*4)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*5)),(y-int(box/2))),2,(150,0,0),-1)
    
def drawleftfront( x, y ):
    global box
    global robotmargin
    cv2.circle(img,((x+int(box/2)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*2)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*3)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*4)),(y-int(box/2))),2,(0,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*5)),(y-int(box/2))),2,(0,0,0),-1)
    
    cv2.circle(img,((x+int(box/2)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*2)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*3)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*4)),(y-int(box/2))),2,(150,0,0),-1)
    cv2.circle(img,((x+(int(box/5)*5)),(y-int(box/2))),2,(150,0,0),-1)
    
def plot( mag , theta, originx, originy ):
    mag1 = mag * 4
    if mag < 50 and mag > 5:
        px = mag1 * np.cos(math.radians(theta)) 
        py = mag1 * np.sin(math.radians(theta))
        plotx = int(px) + originx
        ploty = int(py) + originy
        cv2.circle(img,(plotx,ploty),0,(255,255,255),0)

img = np.zeros([height, width, 3], np.uint8)
#cv2.rectangle(img,(margin,margin),((width - margin),(height - margin)),(74,131,33),2,0)

#for i in range(0,divisions):
#    cv2.line(img,((margin+(i*box)),margin),((margin+(i*box)),width-margin),(25,45,15),1,0)
#    cv2.line(img,(margin,(margin+(i*box))),(height-margin,(margin+(i*box))),(25,45,15),1,0)

global ser
serialBegin()

while True:
    ser.write('S')
    Direction = serialRead()
    if Direction == 'F':
        count1 = count1 + 1
        if count1 == 2:
            flag1 = 0
            count1 = 0
            
        if count == 0:
            inty = inty - box
            drawfront(intx,inty)
            xval = intx + int(box/2)
            yval = inty - box + robotmargin
            for i in range(360,180,-3):
                y = serialRead()
                try:
                    x = int(y)
                except:
                    Direction = y
                    break
                plot(x,i,xval,yval)
                time.sleep(.05)
        elif count == 1:
            intx = intx + box
            drawrightfront(intx,inty)
            xval = intx + int(box/2)
            yval = inty - box + robotmargin
            for i in range(450,270,-3):
                y = serialRead()
                try:
                    x = int(y)
                except:
                    Direction = y
                    break
                plot(x,i,xval,yval)
                time.sleep(.05)
            
        elif count == 2:
            inty = inty + box
            drawback(intx,inty)
            xval = intx + int(box/2)
            yval = inty - box + robotmargin
            for i in range(180,0,-3):
                y = serialRead()
                try:
                    x = int(y)
                except:
                    Direction = y
                    break
                plot(x,i,xval,yval)
                time.sleep(.05)
            
        elif count == 3:
            intx = intx - box
            drawleft(intx,inty)
            xval = intx + int(box/2)
            yval = inty - box + robotmargin
            for i in range(270,90,-3):
                y = serialRead()
                try:
                    x = int(y)
                except:
                    Direction = y
                    break
                plot(x,i,xval,yval)
                time.sleep(.05)
            intx = intx - box
        
    if Direction == 'R':
        if flag1 == 0:
            if count == 0:
                drawright(intx,inty)
            elif count == 1:
                drawback(intx,inty)
            elif count == 2:
                drawleft(intx,inty)
            elif count == 3:
                drawright(intx,inty)
            count = count + 1
            if count == 4:
                count = 0
        flag1 = flag1 + 1
        
    #print Direction
    cv2.imshow('image',img)
    cv2.waitKey(10)
serialClose()
cv2.destroyAllWindows()
