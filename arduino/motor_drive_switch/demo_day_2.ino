#include <PIDLoop.h>
#include <Pixy2Video.h>
#include <Pixy2I2C.h>
#include <Pixy2SPI_SS.h>
#include <Pixy2.h>
#include <Pixy2CCC.h>
#include <TPixy2.h>
#include <Pixy2Line.h>

#include <SoftwareSerial.h>
#include <stdint.h>

Pixy2 pixy;

// drive motor 1 pins
const int IN1 = 5;
const int IN2 = 4;
const int ENA = 6;
//drive motor 2 pins
const int IN3 = 8;
const int IN4 = 7;
const int ENB = 9;
//rate of pwm speed
int rate = 120;
int rate_back = 120;
int i = 0; int j = 0;
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
  Serial.print("\t\t...Starting...\n");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // perform initial 2 sweeps
  sweep ();
  sweep ();  
}

void loop () 
{
  while(TooClose == false) 
  {
  // do this loop until the "too close" flag is raised
  search ();
  area = (pixy.ccc.blocks[i].m_width * pixy.ccc.blocks[i].m_height);
  // area calculated using the block width and height as provided by PixyCam in pixels 
  maxArea = area + 1000;
  minArea = area - 1000;
  
  if (pixy.ccc.numBlocks)
  {
    // if there are blocks detected withing the set color and size parameters
    // then run this loop
    newarea = width * height;
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      // run this loop for every block detected on screen, of the correct color signiture
      area = (pixy.ccc.blocks[i].m_width * pixy.ccc.blocks[i].m_height);
      // re-calculate area as objects may have moved since last measurement
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
      Serial.print("  Area: \t");
      Serial.print(area); Serial.print("\nNew Area: \t"); Serial.print(newarea); Serial.print("\n"); 
      // below is the logic block used to keep an already determined block within
      // the middle of the view of the PixyCam. 
      // The 
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
      // the below block indicates the target is between the left and right turn parameters      
      if(pixy.ccc.blocks[i].m_x>100 && pixy.ccc.blocks[i].m_x<220)
      {      
      motor1_fwd(); motor2_fwd();
      delay(300);
      }
            
      // Below is the loop which checks to see that the last measured area is not bigger than expected
      // if the area is over the set value, determined experimentally
      // then the "too close" and "dump" flags are flipped to true, and the robot stops
      // so that on the next pass of the loop, the bot knows it has reached a wall, after having been
      // aiming itself to the trash bin
      if(area > 30000)
      {
       motor1_bck(); motor2_bck;
       delay(100); 
       Serial.println("\n\tTOO CLOSE\n");
       TooClose = true;
       Dump_Bool = true;
      }
      // it is also possible for the too close flag to be raised due to input from the LIDAR sensors
      // but the dump function would not be executed bc that flag would not have been rasied.
      motor1_stop(); motor2_stop(); 
      delay (5);                            
    }
  }
  else 
  {
    // this else part of the loop is reached if no Bins are visible
    // (idenitfied by color) in the current field of view. 
      Serial.print("\t...panning...searching...panning... loop : ");
      Serial.print(j); Serial.println(" ");
      left_turn(); delay(250); 
      motor1_stop(); motor2_stop(); delay(250);
      motor1_fwd();
      motor2_fwd();
      delay (200);
      motor1_stop(); motor2_stop(); 
      delay (1000);     
  }
    
  
 }
  if ((TooClose) && (Dump_Bool))
  {
    // this loop could be called the dump loop
    // it is entered into after the robot has been navigating to the bins
    // and the wall is reached, determiend visually.
    Serial.println("Arrived at Destinastion");
    delay(3000);
    turn_around();
    delay(3000);
    dump (); Dump_Bool = false;
    delay(3000);
    TooClose = false;
    // after robot is spun to face the field again, and dumping is complete,
    // the two flags are lowered so that the sweep function can continue with the 
    // nearest trash strategy
    sweep();
    exit(0);
  }
}



////////////////////////////////////
void sweep()
{
  // area sweep function
  // called when in known vicinity of trash or at the beginnign of program
  motor1_stop(); motor2_stop();
  delay(500);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop();
  delay (50);
  right_turn();
  delay (1150);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop();
  delay (750);
  right_turn();
  delay (1150);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop(); 
  delay (750);
  right_turn();
  delay (1150);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop();
  delay (750);
  right_turn();
  delay (1150);
  motor1_fwd();
  motor2_fwd();
  delay (600);
  motor1_stop(); motor2_stop();
}

void search()
{
  Serial.print("\tPixy Search for Trash Bin\t");
  motor1_stop(); motor2_stop();
  uint16_t blocks;
  Serial.print("\nScanning\n");
  blocks = pixy.ccc.getBlocks();
  // ^ is the actual execution of the pixy.get color coded blocks
  // only runs when searching to lessen computing rescources occupied 
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
  // currently time dependant dump function
  // runs on second arduino after pre determiend time frame
  // next step is to change to digital I/O signal
}

void turn_around()
{
  Serial.println("Spin function call");
  right_turn();
  delay(2000);
  motor1_stop(); motor2_stop();
}
