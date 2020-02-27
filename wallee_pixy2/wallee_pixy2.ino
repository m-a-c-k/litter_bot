#include <Servo.h>

#include <SoftwareSerial.h>

#define enA 6
#define enB 9
#define in1 5
#define in2 4
#define in3 8
#define in4 7

#include <Pixy2.h>

// This is the main Pixy object 
Pixy2 pixy;

int i, j;
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
int pwmOutput = 255;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
 
  Serial.begin(115200);
  Serial.print("...Starting...\n");
  pixy.init();
  pixy.setLamp(0, 0);
  delay(500);
   // value from 0 to 255
  analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
  analogWrite(enB, pwmOutput);

  sweep_field();
}
void loop() {
  
  //int pwmOutput = 200; // value from 0 to 255
  analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
  analogWrite(enB, pwmOutput);

  while(millis()<5000)
  {
    scan();
    area = width * height;
    maxArea = area + 1000;
    minArea = area - 1000;
  }

  scan();
 pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks)
  //if (signature ==1)
  {
    newarea = width * height;
    
    pwmOutput = 255;
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
      Serial.print("  Area: ");
      Serial.print(area); Serial.print("\n");
      area = (pixy.ccc.blocks[i].m_width * pixy.ccc.blocks[i].m_height);
          
      if(pixy.ccc.blocks[i].m_x<=100)
      {      
      lft();  
      delay(10); 
      }   

      if(pixy.ccc.blocks[i].m_x>=220)
      {      
      rght();      
      delay(10); 
      }
            
      if(pixy.ccc.blocks[i].m_x>100 && pixy.ccc.blocks[i].m_x<220)
      {      
      fwd();
      delay(200);
      }
            
      
      else if(newarea > maxArea)
      {
       bck(); delay(50); 
      }

      stp(); 
      delay (5);                            
    }
  }  

    else {
      
         scan(); delay(300);
    }

}

/////////////////////////////////////////////////////////////////////////////////
void scan()
{
 uint16_t blocks;
 Serial.print("\nScanning");
 blocks = pixy.ccc.getBlocks();
 delay(10);
  
}
void fwd()
{
  Serial.print("\nforward\n");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
}

void fwd2()
{
  Serial.print("\nforward 2\n");
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, pwmOutput);
}

void bck()
{
  Serial.print("\nback\n");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void lft()
{
  Serial.print("\nleft\n");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}

void rght()
{
  Serial.print("\nright\n");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stp()
{
  Serial.print("\nhalt!\n");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void search()
{
  Serial.print("\nSESRCHING\n");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void sweep_field()
{
  
  fwd();  fwd2(); delay(2000);
  stp();  delay (5);
  rght(); delay (240);
  stp();  delay (5);
  fwd();  fwd2(); delay(400);
  stp();  delay (5);
  rght(); delay (240);
  stp();  delay (5);
  fwd();  fwd2(); delay(2000);
  stp();  delay (5);
  lft();  delay (240);
  stp();  delay (5);
  fwd();  fwd2(); delay(400);
  stp();  delay (5);
  lft();  delay (240);
  stp();  delay (5);
  fwd();  fwd2(); delay(2000);
  stp();   delay (5);
  rght(); delay (240);
  stp();  delay (5);
  fwd();  fwd2(); delay(400);
  stp();  delay (5);
  rght(); delay (240);
  stp();  delay (5);
  fwd();  fwd2(); delay(2000);
  stp();  delay (5);
  lft();  delay (240);
  stp();  delay (5);
  fwd(); fwd2();  delay(400);
  stp();  delay (5);
  lft();  delay (240);
  stp();  delay (5);
      
}
