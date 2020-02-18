import time

class RobotStates:
  IDLE = 1
  SEARCH = 2
  FOLLOW = 3
  ARRIVED = 4
  DUMP = 5
  SWEEP = 6
  LOOK_FOR_BIN = 7
  
  
currentState = RobotStates.IDLE


while True:
    print("\n<read from camera and sensors>\n")
    print ("Current State:       ",currentState)
    
    if (currentState == RobotStates.IDLE):
		currentState = RobotStates.FOLLOW
		time.sleep(3)
		
	elif (currentState == RobotStates.FOLLOW):
		fwd()
		time.sleep(3)
        
          

def search (): 
	print("searching")

def fwd():
	print("forward")

def bck():
	print("backward")
	
def lft():
	print("forward")
	
def rght():
	print("forward")	

def halt():
	print("stop moving")

