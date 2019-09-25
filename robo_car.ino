//This demo is used for testing the ultrasonic module.
//Connect the module to Arduino UNO trig -> A2  echo ->A3
//When the code start, it will print the value of the ultrasonic
//to the serial montor
#include <UCMotor.h>
#include <Servo.h>


#define TRIG_PIN A2
#define ECHO_PIN A3
UC_DCMotor leftMotor1(3, MOTOR34_64KHZ);
UC_DCMotor rightMotor1(4, MOTOR34_64KHZ);
UC_DCMotor leftMotor2(1, MOTOR34_64KHZ);
UC_DCMotor rightMotor2(2, MOTOR34_64KHZ);


void setup()
{
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT); //Set the connection pin output mode Echo pin
  pinMode(TRIG_PIN, OUTPUT);//Set the connection pin output mode trog pin
}

void fwd() {
  Serial.println("Forwards");
  leftMotor1.run(0x02); rightMotor1.run(0x02);
  leftMotor2.run(0x02); rightMotor2.run(0x02);
  leftMotor1.setSpeed(100); rightMotor1.setSpeed(100);
  leftMotor2.setSpeed(100); rightMotor2.setSpeed(100);
}

void lft() {
  Serial.println("Backup, Turn");
  leftMotor1.run(0x01); rightMotor1.run(0x01);
  leftMotor2.run(0x01); rightMotor2.run(0x01);
  leftMotor1.setSpeed(100); rightMotor1.setSpeed(100);
  leftMotor2.setSpeed(100); rightMotor2.setSpeed(100);
  delay(100);
  leftMotor1.run(0x03); rightMotor1.run(0x03);
  leftMotor2.run(0x03); rightMotor2.run(0x03);
  leftMotor1.setSpeed(200); rightMotor1.setSpeed(200);
  leftMotor2.setSpeed(200); rightMotor2.setSpeed(200);  
}

void bck() {
  Serial.println("Backwards");
  leftMotor1.run(0x01); rightMotor1.run(0x01);
  leftMotor2.run(0x01); rightMotor2.run(0x01);
  leftMotor1.setSpeed(100); rightMotor1.setSpeed(100);
  leftMotor2.setSpeed(100); rightMotor2.setSpeed(100);
}

void loop(){
  int temp = readPing();
  Serial.println(temp,DEC);
  
  if (temp > 10)
    fwd();        
  
  if ( temp < 25)
     lft();  
  
  if ( temp < 15 ) 
      bck();      
  
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
