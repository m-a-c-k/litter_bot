
#include <SoftwareSerial.h>
#include <stdint.h>

const int IN1 = 5;
const int IN2 = 4;
const int ENA = 6;

const int IN3 = 8;
const int IN4 = 7;
const int ENB = 9;

int rate = 200;
int rate_back = 100;

void setup()
{
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop () 
{
  motor1_stop();
  motor2_stop();
  delay(500);
  motor1_fwd();
  motor2_fwd();
  delay (500);
  motor1_bck();
  motor2_bck();
  delay (1000);
  left_turn();

}




void motor1_stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW); 
  Serial.print("stop"); 
}

void motor2_stop()
{  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
    Serial.print("stop2"); 

}

void motor1_fwd()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, rate);
    Serial.print("fwd\t"); 
  
}

void motor2_fwd()
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, rate);
    Serial.print("fwd2\t"); 

}

void motor1_bck()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, rate_back);
  Serial.print("bck\t");
}

void motor2_bck()
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, rate_back);
  Serial.print("bck2\t");
}

void left_turn ()
{
  motor1_fwd(); motor2_bck();
  delay (500);
  motor1_stop(); motor2_stop();
  Serial.print("Leftzig\n");
}
