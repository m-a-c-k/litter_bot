from lidar_lite import Lidar_Lite
lidar = Lidar_Lite()

connected = lidar.connect(1)
tooClose = False



def scan_li(c):
	for i in range(c):
		distance = lidar.getDistance()
		print ("Distance to target = ", distance)
		if (int(distance) < 20):
			tooClose = True
			print ("\nToo Close!!! Back Off!!\n")

		if (int(distance) > 35):
			tooClose = False
			print("\nProceed\n")






if (__name__) == "__main__":
	if connected < -1:
		print ("Not Connected")
	else:
		print ("Connected")
	while (connected >= -1):
		s = str(input("Start Scanning?y/n : "))

		if (s == 'y'):
			scan_li(100)
		if (s == 'n'):
			print("\nNo scanning then.\n")
			exit(0)
