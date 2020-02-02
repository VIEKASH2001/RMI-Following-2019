# import the necessary packages
import cv2

class noofsides:
    def detect(self, c): # c is the contour of the shape to be found

     # the below 2 functions are to find the number of sides that the polygon has
     peri = cv2.arcLength(c, False)
     approx = cv2.approxPolyDP(c, 0.04 * peri, False)
     sides=len(approx) #this is to store the number of sides
     coordinate=((sides)-4) #this is the final coordinate
     return coordinate
		
