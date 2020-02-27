#include <PIDLoop.h>
#include <ZumoBuzzer.h>
#include <Pixy2Video.h>
#include <Pixy2I2C.h>
#include <Pixy2SPI_SS.h>
#include <ZumoMotors.h>
#include <Pixy2.h>
#include <Pixy2CCC.h>
#include <TPixy2.h>
#include <Pixy2Line.h>

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
int i = 0;

Pixy2 pixy;

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
  while (i <= 3) 
  {
    Serial.print("Loop #: "); Serial.print(i, DEC); Serial.print(" ");
    sweep();
    i++;
  }

  search ();
  
if (pixy.ccc.numBlocks)
  {
    Serial.println("Found\n");
  }
  
else 
    {
      Serial.println("Not Yet Found\n");  
    }
  
}



////////////////////////////////////
void sweep()
{
  motor1_stop();
  motor2_stop();
  delay(500);
  motor1_fwd();
  motor2_fwd();
  delay (1000);
  motor1_bck();
  motor2_bck();
  delay (500);
  left_turn();
  delay (500);
}

void search()
{
  Serial.print("Pixy Search for Trash Bin");
  uint16_t blocks;
  Serial.print("\nScanning\n");
  blocks = pixy.ccc.getBlocks();
  delay(10);
}

void motor1_stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW); 
  Serial.print("stop\t"); 
}

void motor2_stop()
{  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
    Serial.print("stop2\t"); 

}

void motor1_fwd()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, rate);
    Serial.print("fwd1\t"); 
  
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
