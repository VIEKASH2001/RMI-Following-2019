# import the necessary packages
import cv2

class noofdefects:
    def detect(self,c): # c is the contour of the shape to be found
        
     #find contour of max area(hand)
     cnt = max(c, key = lambda x: cv2.contourArea(x))
        
     #approx the contour a little
     epsilon = 0.0005*cv2.arcLength(cnt,True)
     approx= cv2.approxPolyDP(cnt,epsilon,True)
       
        
     #make convex hull around hand
     hull = cv2.convexHull(cnt)
        
     
     #find the defects in convex hull with respect to hand
     hull = cv2.convexHull(approx, returnPoints=False)
     defects = cv2.convexityDefects(approx, hull)
        
     # l = no. of defects
     l=0

     if defects is not None:
    
       #code for finding no. of defects due to fingers
       for i in range(defects.shape[0]):
          l+=1
     

     l=l-3
     return l
