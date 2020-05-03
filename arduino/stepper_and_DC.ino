// by Uriel Lua for Wall-E
//including library for stepper and number of steps
#include <Stepper.h>
const int stepsPerRevolution = 200;
//setting pins for DC motor sweeper 
const int pwm = 2 ;  
const int in_1 = 6 ;
const int in_2 = 7 ;
//setting pins for stepper
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int count = 0;  // number of steps the motor has taken
int sweep = 1;
void setup() {
 // initialize the serial port:
Serial.begin(115200);
pinMode(pwm,OUTPUT) ;   //we have to set PWM pin as output
pinMode(in_1,OUTPUT) ;  //Logic pins are also set as output
pinMode(in_2,OUTPUT) ;
//-----starting the DC mot
}

void loop() {
// -----start the DC motor for sweep-----
//or for dump-----

  while( sweep < 50 )
 {
    digitalWrite(in_1,LOW) ;
    digitalWrite(in_2,HIGH) ;
    analogWrite(pwm,199) ;
    Serial.println("\nSpin ON\n"); Serial.println(sweep); 
    Serial.print(" ");
    sweep++;
    delay(500);
  }

  if (sweep >= 50)
  {
    digitalWrite(in_1,LOW) ;
    digitalWrite(in_2,HIGH) ;
    analogWrite(pwm,150) ;
    //----starting steper loop----
    myStepper.step(-1);
    Serial.print("steps:");
    Serial.println(count);
    count++;
    delay(3);
  
    if (count == 1120) {
    
    delay (1000);
    count++;
    }
  
    while (count >1120 && count < 2240) 
    {
      //--DC going backwards--
      digitalWrite(in_1,HIGH) ;
      digitalWrite(in_2,LOW) ;
      analogWrite(pwm,180) ;
      //--stepper going down--
      Serial.println("-steps");
      Serial.println(count);
      myStepper.step(1);
      count ++;
      delay(5);
    }
   if (count >= 2240) 
   {
    analogWrite(pwm,180) ;
    Serial.println(count);
    Serial.println("STOP");
    myStepper.step(0);
    exit(0);
    }
  }


}
