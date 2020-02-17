const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
bool      tooClose;
long duration, inches, cm;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   fwd();
}


void loop() {
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   //Serial.print(duration);
   Serial.print("\n");
   Serial.print(cm);
   Serial.print("cm\n");
   Serial.println();
   delay(100);

  if (cm < 10){
    detected();
    tooClose = true;
  }
  else {
    tooClose =false;
    fwd();
  }
  delay(10);
  
  
  
  
  
}




long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void detected(){
  Serial.print("too close\n");
  delay(500);
}

//------------------------------------------------------//
void fwd(){
  //
  Serial.print("forward\n");
}

void rotate_lft(){
  //
}

void rotate_right(){
  //
}

void bck(){
  //
}

void halt(){
 //
}

