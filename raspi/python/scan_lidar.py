from lidar_lite import Lidar_Lite
lidar = Lidar_Lite()

connected = lidar.connect(1)

if connected < -1:
	print ("Not Connected")
else:
	print ("Connected")

s = str(input("Start Scanning?y/n : "))

if (s == 'y'):
	for i in range(1000):
		distance = lidar.getDistance()
		print ("Distance to target = ", distance)
		if (int(distance) < 20):
        		print ("Too Close!!! Back Off!!")
if(s == 'n'):
	print("\nNo scanning then.\n")
	exit(0)
