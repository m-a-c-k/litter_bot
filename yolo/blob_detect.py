#!/usr/bin/python

# Standard imports
import cv2
import numpy as np
import time

# Read image
im = cv2.imread("blob.jpg", cv2.IMREAD_GRAYSCALE)
cap = cv2.VideoCapture(0)
i = 0

# Setup SimpleBlobDetector parameters.
params = cv2.SimpleBlobDetector_Params()

# Change thresholds
params.minThreshold = 10
params.maxThreshold = 400


# Filter by Area.
params.filterByArea = True
params.minArea = 100
params.maxArea=4000

# Filter by Circularity
params.filterByCircularity = False
params.minCircularity = 0.001

# Filter by Convexity
params.filterByConvexity = True
params.minConvexity = 0.87
    
# Filter by Inertia
params.filterByInertia = True
params.minInertiaRatio = 0.0001

# Grouping
params.minDistBetweenBlobs = 20

params.filterByColor = False
params.blobColor = 225

# Create a detector with the parameters
ver = (cv2.__version__).split('.')
if int(ver[0]) < 3 :
	detector = cv2.SimpleBlobDetector(params)
else : 
	detector = cv2.SimpleBlobDetector_create(params)

while(True):
# Detect blobs.
	#keypoints = detector.detect(im)
	ret, frame = cap.read()
	keypoints = detector.detect(frame)

# Draw detected blobs as red circles.
# cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS ensures
# the size of the circle corresponds to the size of blob

	#im_with_keypoints = cv2.drawKeypoints(im, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	cap_w_keypoints = cv2.drawKeypoints(frame, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	
	
# Show blobs
	#cv2.imshow("Keypoints", im_with_keypoints)
	cv2.imshow('frame',cap_w_keypoints)
	#cv2.waitKey(0)
	
	pts = cv2.KeyPoint_convert(keypoints)
	print("keypoints: ", pts)
#-----------------------------------------------------------------------

# Text Box
	#img = np.zeros((500,800,3),np.uint8)
	#response= str(pts)

#	cv2.putText(img, response,(0, 50),
 #              cv2.FONT_HERSHEY_SIMPLEX,
  #             1,(0, 0, 255),
   #            lineType=cv2.LINE_AA)
               
#	cv2.imshow('frame2', img)
#-----------------------------------------------------------------------
	
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
	
	

cap.release()
cv2.destroyAllWindows()
