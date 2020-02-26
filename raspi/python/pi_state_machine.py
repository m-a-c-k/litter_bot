import time
from lidar_lite import Lidar_Lite
lidar = Lidar_Lite()


class RobotStates:
  IDLE = 1
  SEARCH = 2
  FOLLOW = 3
  ARRIVED = 4
  DUMP = 5
  SWEEP = 6
  LOOK_FOR_BIN = 7
  REV = 8
  STOP = 9
  
connected = lidar.connect(1)
tooClose = False
currentState = RobotStates.STOP

i=0
    
    
def scan_li(c):
	for i in range(c):
		distance = lidar.getDistance()
		print ("Distance to target = ", distance)
		if (int(distance) < 20):
			tooClose = True
			print ("\nToo Close!!! Back Off!!\n")

		elif (int(distance) > 35):
			tooClose = False
			print("\nProceed\n")


def search ():
	return (5,6)
	
def track():
	return ("arrived")


def fwd():
	scan_li(10)
	print("forward")

def bck():
	print("backward")
	
def lft():
	print("forward")
	
def rght():
	print("forward")	

def halt():
	print("stop moving")

def dumpFunction():
	print("dumping")
	return ("Dumped")
	

 
while True:
	print("loop: ", i)
	i += 1
	if (tooClose == True):
		bck()
		currentState = RobotStates.REV  
	if (currentState == RobotStates.IDLE):
		print("STATE: ", currentState)
		currentState = RobotStates.SEARCH
	
	if (currentState == RobotStates.SEARCH):			
		print("...searching...")
		if (search() == (5,6)):
			print("coordinates: ",search())
			currentState = RobotStates.FOLLOW
			
			
	elif (currentState == RobotStates.FOLLOW):
		print("STATE: ", currentState)
		fwd()
		if (track() == "arrived"):
			currentState = RobotStates.ARRIVED
			halt()
			
	elif (currentState == RobotStates.ARRIVED):
		print("STATE: ", currentState)
		print("\nhere\n")
		currentState = RobotStates.DUMP
	
	elif (currentState == RobotStates.DUMP):
		print("STATE: ", currentState)
		if (dumpFunction() == "Dumped"):
			print("All dumped out")
			currentState = RobotStates.IDLE		
	elif (currentState == RobotStates.REV):
		print("STATE: ", currentState)
		if (tooClose == False) :
			currentState = RobotStates.FOLLOW
		else:
			currentState = RobotStates.REV

	elif (currentState == RobotStates.STOP):
		print(tooClose)
		if (tooClose == False):
			currentState = RobotStates.SEARCH
		print("STATE: ", currentState)
		halt()

	time.sleep(2)
