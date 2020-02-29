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

Pixy2 pixy;

const int IN1 = 5;
const int IN2 = 4;
const int ENA = 6;

const int IN3 = 8;
const int IN4 = 7;
const int ENB = 9;

int rate = 120;
int rate_back = 120;
int i = 0;
int signature = 0;
int x = 0;
int y = 0;
unsigned int width = 0;
unsigned int height = 0;
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 70;
int Xmax = 200;
int maxArea = 0;
int minArea = 0;
bool TooClose = false;
bool Dump_Bool = false;


void setup()
{
  pixy.init();
  Serial.begin(115200);
  Serial.print("...Starting...\n");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  /*while (i <= 3) 
  {
    Serial.print("Loop #: "); Serial.print(i, DEC); Serial.print(" ");
    sweep();
    i++;
  }*/
  sweep ();
  
  
}

void loop () 
{
  while(TooClose == false)
  {
 
  search ();
  area = (pixy.ccc.blocks[i].m_width * pixy.ccc.blocks[i].m_height);
  maxArea = area + 1000;
  minArea = area - 1000;
  
  if (pixy.ccc.numBlocks)
  {
    newarea = width * height;
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      area = (pixy.ccc.blocks[i].m_width * pixy.ccc.blocks[i].m_height);
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
      Serial.print("  Area: \t");
      Serial.print(area); Serial.print("\nNew Area: \t"); Serial.print(newarea); Serial.print("\n"); 
      
          
      if(pixy.ccc.blocks[i].m_x<=100)
      {      
        left_turn();
        delay(30); 
      }   

      if(pixy.ccc.blocks[i].m_x>=220)
      {      
        right_turn();    
        delay(30); 
      }
            
      if(pixy.ccc.blocks[i].m_x>100 && pixy.ccc.blocks[i].m_x<220)
      {      
      motor1_fwd(); motor2_fwd();
      delay(300);
      }
            
      
      if(area > 38000)
      {
       motor1_bck(); motor2_bck;
       delay(100); 
       Serial.println("\n\tTOO CLOSE\n");
       TooClose = true;
       Dump_Bool = true;
      }

      motor1_stop(); motor2_stop(); 
      delay (5);                            
    }
  } 
 }
  if ((TooClose) && (Dump_Bool))
  {
    Serial.println("Arrived at Destinastion");
    delay(3000);
    turn_around();
    delay(3000);
    dump (); Dump_Bool = false;
    delay(3000);
    TooClose = false;
    //sweep();
    exit(0);
  }
}



////////////////////////////////////
void sweep()
{
  motor1_stop(); motor2_stop();
  delay(500);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop();
  delay (50);
  right_turn();
  delay (1050);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop();
  delay (750);
  right_turn();
  delay (1050);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop(); 
  delay (750);
  right_turn();
  delay (1050);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop();
  delay (750);
  right_turn();
  delay (1050);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop();
}

void search()
{
  Serial.print("Pixy Search for Trash Bin");
  motor1_stop(); motor2_stop();
  uint16_t blocks;
  Serial.print("\nScanning\n");
  blocks = pixy.ccc.getBlocks();
  right_turn(); delay (100); left_turn(); delay(100);
  motor1_stop(); motor2_stop(); delay(10);
}

void motor1_stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW); 
  Serial.print("stop1\t"); 
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
  Serial.print("Leftzig\n");
}

void right_turn ()
{
  motor1_bck(); motor2_fwd();
  Serial.print("Richtzig\n");

}

void dump()
{
  Serial.println("Dump function call"); 
}

void turn_around()
{
  Serial.println("Spin function call");
  right_turn();
  delay(2000);
  motor1_stop(); motor2_stop();
}
