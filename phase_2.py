#image processing program   `
import cv2
import serial
import time
#bluetooth serial port
a="COM12"
ard=serial.Serial(a,9600)
#declaring arrays and variables
area_array=[]
contours=[]
l=0 #defects counter
i=0 #condition variable
cap = cv2.VideoCapture(0)
while True:
    
    #capture the image
    
    while(1):
        _, frame = cap.read()
        cv2.imshow('frame', frame)
        k = cv2.waitKey(5)
        if k==27:
            break
    cv2.imwrite("F:\capture.png",frame)

    # crop the image using ROI(Region Of Intrest)
    r = cv2.selectROI(frame)
    imcrop = frame[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
    cv2.imshow("Image", imcrop)

    # convert the resized image to grayscale, blur it slightly, threshold it and contour it
    gray = cv2.cvtColor(imcrop, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    _,thresh = cv2.threshold(blurred, 50, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
    _,contours,hierarchy= cv2.findContours(thresh,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)

    #to create a contour array from the image and make it into a 2X2 matrix with:
    #sort[0][0] area of the shape is stored in here
    #sort[0][1] contour pts of shapes are stored in here
    #sort[1][0] area of the radial line is stored in here
    #sort[1][1] contour pts of radial lines are stored in here
    for c in contours:
        hull = cv2.convexHull(c, returnPoints=False)
        defects = cv2.convexityDefects(c, hull)
    for i,c in enumerate(contours):
        area=cv2.contourArea(c)
        area_array.append(area)
    mapped=zip(area_array,contours)
    sort=sorted(mapped,key=lambda x: x[0],reverse=True)

    #assigning variable names for the respective contour pts
    shacnt=sort[0][1]
    radcnt=sort[1][1]

    #the defects in the radial lines is calculated and the Y COORDINATE IS FOUND
    hull = cv2.convexHull(radcnt, returnPoints=False)
    defects = cv2.convexityDefects(radcnt, hull)
    l=0
    if defects is not None:
      for i in range(defects.shape[0]):
         l+=1
    Y=l-3

    #the side length of the shapes is calculated and the X COORDINATE IS FOUND
    peri = cv2.arcLength(shacnt, False)
    approx = cv2.approxPolyDP(shacnt, 0.04 * peri, False)
    sides=len(approx) #this is to store the number of sides
    X=sides-4 #this is the final coordinate


    #display the required info
    print("the X coordinate is: ")
    print(X)
    print("the Y coordinate is: ")
    print(Y)
    print("if you want to change the coordinates enter 0 else enter 1")
    i=input()
    C=(10*X + Y)
    print(C)
    ard.write(str.encode(str(C)))
    ard.flush();
    print("LET THE FOLLOWING BEGIN!!!")
    cv2.destroyAllWindows();



