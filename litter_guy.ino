
#include <UCMotor.h>
#include <Servo.h> 


#define TRIG_PIN A2
#define ECHO_PIN A3
UC_DCMotor leftMotor1(3, MOTOR34_64KHZ);
UC_DCMotor rightMotor1(4, MOTOR34_64KHZ);
UC_DCMotor leftMotor2(1, MOTOR34_64KHZ);
UC_DCMotor rightMotor2(2, MOTOR34_64KHZ);
Servo myservo;
int pos = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT); //Set the connection pin output mode Echo pin
  pinMode(TRIG_PIN, OUTPUT);//Set the connection pin output mode trog pin
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object  
}

void loop(){
  int temp = readPing();
  Serial.println(temp,DEC);
  if (temp > 15){
    //Backward- motors confused
        Serial.println("Forwards");
        leftMotor1.run(0x02); rightMotor1.run(0x02);
        leftMotor2.run(0x02); rightMotor2.run(0x02);
        leftMotor1.setSpeed(100); rightMotor1.setSpeed(100);
        leftMotor2.setSpeed(100); rightMotor2.setSpeed(100);
        delay(200);
        leftMotor1.setSpeed(0); rightMotor1.setSpeed(0);
        leftMotor2.setSpeed(0); rightMotor2.setSpeed(0);
        delay(500);
        
  }
  if ( temp < 25) {
     //left
        Serial.println("Turn");
        leftMotor1.run(0x03); rightMotor1.run(0x03);
        leftMotor2.run(0x03); rightMotor2.run(0x03);
        leftMotor1.setSpeed(200); rightMotor1.setSpeed(200);
        leftMotor2.setSpeed(200); rightMotor2.setSpeed(200);
        delay(400);
  }
  if ( temp < 15 ) {  
    //Forward- motors confused
        Serial.println("Backwards");
        leftMotor1.run(0x01); rightMotor1.run(0x01);
        leftMotor2.run(0x01); rightMotor2.run(0x01);
        leftMotor1.setSpeed(100); rightMotor1.setSpeed(100);
        leftMotor2.setSpeed(100); rightMotor2.setSpeed(100);
        delay(200);
  }
  delay(50);
  
  for(pos = 0; pos < 60; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
  for(pos = 60; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
  
  
  }

int readPing()
{
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, cm;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, LOW);

  pinMode(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  return cm ;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

