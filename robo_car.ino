
#include <UCMotor.h>
#include <Servo.h>
#include "UCNEC.h"

#define LSensor A0
#define MSensor A1
#define RSensor 13

#define TRIG_PIN A2
#define ECHO_PIN A3
UC_DCMotor leftMotor1(3, MOTOR34_64KHZ);
UC_DCMotor rightMotor1(4, MOTOR34_64KHZ);
UC_DCMotor leftMotor2(1, MOTOR34_64KHZ);
UC_DCMotor rightMotor2(2, MOTOR34_64KHZ);

int SPEED = 100;
Servo myservo;
int pos = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT); //Set the connection pin output mode Echo pin
  pinMode(TRIG_PIN, OUTPUT);//Set the connection pin output mode trog pin
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void fwd() {
  Serial.println("Forwards");
  leftMotor1.run(0x02); rightMotor1.run(0x02);
  leftMotor2.run(0x02); rightMotor2.run(0x02);
  leftMotor1.setSpeed(100); rightMotor1.setSpeed(100);
  leftMotor2.setSpeed(100); rightMotor2.setSpeed(100);
  delay(100);
}

void lft() {
  Serial.println("Left Turn");
  leftMotor1.run(0x03); rightMotor1.run(0x03);
  leftMotor2.run(0x03); rightMotor2.run(0x03);
  leftMotor1.setSpeed(80); rightMotor1.setSpeed(80);
  leftMotor2.setSpeed(80); rightMotor2.setSpeed(80);
  delay(100);
}

void rght() {
 Serial.println("Left Turn");
 leftMotor1.run(0x04); rightMotor1.run(0x04);
 leftMotor2.run(0x04); rightMotor2.run(0x04);
 leftMotor1.setSpeed(80); rightMotor1.setSpeed(80);
 leftMotor2.setSpeed(80); rightMotor2.setSpeed(80);
 delay(100);  

}

void bck() {
  Serial.println("Backwards");
  leftMotor1.run(0x01); rightMotor1.run(0x01);
  leftMotor2.run(0x01); rightMotor2.run(0x01);
  leftMotor1.setSpeed(100); rightMotor1.setSpeed(100);
  leftMotor2.setSpeed(100); rightMotor2.setSpeed(100);
  delay(100);
}

void stp() {
  Serial.println("Stop!");
  leftMotor1.run(0x00); rightMotor1.run(0x00);
  leftMotor2.run(0x00); rightMotor2.run(0x00);
  leftMotor1.setSpeed(0); rightMotor1.setSpeed(0);
  leftMotor2.setSpeed(0); rightMotor2.setSpeed(0);
   delay(100);
}

void loop(){
  int temp = readPing();
  Serial.println(temp,DEC);
  int leftRead = 0; midRead = 0; rightRead = 0;
  
  leftread = digitalRead(LSensor);
  midRead = digitalRead(MSensor);
  rightRead = digitalRead(RSensor);        
  
  if ( temp < 25)
     stp();  
  if ((leftRead == 0) && (midRead == 0) && (rightRead == 0 )) 
    stp();
  else if ((leftRead == 0) && (rightRead == 1)) 
    rght();
  else if ((leftRead == 1) && (rightRead == 0))
    lft();
  else 
    fwd();
    
  delay(50);
  
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

void servoSweep() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}


