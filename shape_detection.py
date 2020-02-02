from classes.noofsides import noofsides
from classes.noofdefects import noofdefects
import cv2

cap = cv2.VideoCapture(0)
while(1):

    # Take each frame
    _, frame = cap.read()
    cv2.imshow('frame', frame)
    k = cv2.waitKey(5)
    if k==27:
        break
cv2.imwrite("F:\capture.png",frame)


# Select ROI
r = cv2.selectROI(frame)
#Crop image
imcrop = frame[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
# Display cropped image
cv2.imshow("Image", imcrop)


# convert the resized image to grayscale, blur it slightly and threshold it
gray = cv2.cvtColor(imcrop, cv2.COLOR_BGR2GRAY)
blurred = cv2.GaussianBlur(gray, (5, 5), 0)
_,thresh = cv2.threshold(blurred, 50, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
cv2.imshow("thresh",thresh)


#find contours and draw it
_,contours,hierarchy= cv2.findContours(thresh.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
cnts = cv2.drawContours(imcrop, contours, -1,(0,255,0), 3)
cv2.imshow("cnt",cnts)

    
sd = noofsides()

for c in contours:
  X = sd.detect(c)
     
      
print(X)


