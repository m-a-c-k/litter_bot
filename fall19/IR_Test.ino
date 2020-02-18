#include <UCMotor.h>

#define IR1 A0 // left sensor
#define IR2 A1 // middle sensor
#define IR3 13 // right sensor 

#define START_SPEED 150
#define SPEED 65
#define TURN_SPEED1 150 // soft turn
#define TURN_SPEED2 255 // hard turn

#define FORWARD 1
#define BACKWARD 2

UC_DCMotor leftMotor1(3, MOTOR34_64KHZ);
UC_DCMotor rightMotor1(4, MOTOR34_64KHZ);
UC_DCMotor leftMotor2(1, MOTOR34_64KHZ);
UC_DCMotor rightMotor2(2, MOTOR34_64KHZ);

int left_IR = 1;
int mid_IR = 1;
int right_IR = 1;
int state = 0;  // 3-bit input from  IR sensors  
bool wallDetect = false;

void start_forward() {
  leftMotor1.setSpeed(START_SPEED); 
  leftMotor2.setSpeed(START_SPEED);
  rightMotor1.setSpeed(START_SPEED);
  rightMotor2.setSpeed(START_SPEED);
  
  leftMotor1.run(FORWARD); 
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
  delay(20);
}

void forward() {
  leftMotor1.setSpeed(SPEED); 
  leftMotor2.setSpeed(SPEED); 
  rightMotor1.setSpeed(SPEED);
  rightMotor2.setSpeed(SPEED);
}

void left() {
 leftMotor1.setSpeed(SPEED/1.1); 
 rightMotor1.setSpeed(SPEED);
 leftMotor2.setSpeed(SPEED/1.1); 
 rightMotor2.setSpeed(SPEED);
}

void hard_left() {
 leftMotor1.setSpeed(SPEED/2); 
 rightMotor1.setSpeed(2.5*SPEED);
 leftMotor2.setSpeed(SPEED/2);
 rightMotor2.setSpeed(2.5*SPEED); 
}

void right() {
 leftMotor1.setSpeed(SPEED); 
 rightMotor1.setSpeed(SPEED/1.1);
 leftMotor2.setSpeed(SPEED); 
 rightMotor2.setSpeed(SPEED/1.1);
}

void hard_right() {
 leftMotor1.setSpeed(2.5*SPEED);
 rightMotor1.setSpeed(SPEED/2);
 leftMotor2.setSpeed(2.5*SPEED);
 rightMotor2.setSpeed(SPEED/2);
}

void stop() {
  leftMotor1.setSpeed(0); rightMotor1.setSpeed(0);
  leftMotor2.setSpeed(0); rightMotor2.setSpeed(0);
}

void reverse() {
  leftMotor1.run(BACKWARD); 
  leftMotor2.run(BACKWARD);
  rightMotor1.run(BACKWARD);
  rightMotor2.run(BACKWARD);
  //delay(20);
  leftMotor1.setSpeed(1.2*SPEED); 
  leftMotor2.setSpeed(1.2*SPEED); 
  rightMotor1.setSpeed(1.2*SPEED);
  rightMotor2.setSpeed(1.2*SPEED);
}

void rev_right() {
  leftMotor1.run(BACKWARD); 
  leftMotor2.run(BACKWARD);
  delay(20);
  leftMotor1.setSpeed(1.2*SPEED); 
  leftMotor2.setSpeed(1.2*SPEED);
}

void rev_left() {
  rightMotor1.run(BACKWARD); 
  rightMotor2.run(BACKWARD);
  delay(20);
  rightMotor1.setSpeed(1.2*SPEED); 
  rightMotor2.setSpeed(1.2*SPEED);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //start_forward();
   
}

void loop() {
  // put your main code here, to run repeatedly:

  //wallDetect needs to be a function!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  while(!wallDetect) {  
    left_IR = digitalRead(IR1);
    mid_IR = digitalRead(IR2);
    right_IR = digitalRead(IR3);

    state = 4*left_IR + 2*mid_IR + right_IR;
    Serial.println(state);

    switch(state) {
      case 0:
        start_forward();
        forward();
        break;

      case 1:
        left();        
        break;

       case 3:
        hard_left();
        break;

       case 4:
        right();
        break;

       case 6:
        hard_right();
        break;
       
      case 7:
        stop();
        reverse();
        delay(200);
        stop();
        start_forward();
        forward();

       default:
        forward();
        break;
    }
    
  }

  

}
