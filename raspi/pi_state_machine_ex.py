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

i=0
    
    
def search (): 
	return (5,6)
	
def track():
	return ("arrived")


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

def dumpFunction():
	print("dumping")
	return ("Dumped")
	

 
while True:
	print("loop: ", i)
	i += 1
  
	if (currentState == RobotStates.IDLE):
		print("STATE: ", currentState)
		currentState = RobotStates.SEARCH
	
	if (currentState == RobotStates.SEARCH):			
		print("...searching...")
		if (search() == (5,6)):
			print("coordinates: ",search())
			currentState = RobotStates.FOLLOW
			fwd()
			
	elif (currentState == RobotStates.FOLLOW):
		print("STATE: ", currentState)
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
						
			
			
		
	time.sleep(2)
