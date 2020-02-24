
 
/*------------------------------------------------------------------------------
  LIDARLite Arduino Library
  v3HP/v3HP_I2C
  This example shows methods for running the LIDAR-Lite v3 HP in various
  modes of operation. To exercise the examples open a serial terminal
  program (or the Serial Monitor in the Arduino IDE) and send ASCII
  characters to trigger the commands. See "loop" function for details.
  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite I2C SCL (green) to Arduino SCL
  LIDAR-Lite I2C SDA (blue) to Arduino SDA
  LIDAR-Lite Ground (black) to Arduino GND
  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND
  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3HP_Operation_Manual_and_Technical_Specifications.pdf
------------------------------------------------------------------------------*/

#include <stdint.h>
//#include <Wire.h>
//#include <LIDARLite_v3HP.h>

//LIDARLite_v3HP myLidarLite;

#define FAST_I2C

enum DRIVE_FUNCTION
{
    REST,
    STOP,
    FORWARD,
    BACKWARD,
    LEFT_ROT,
    RIGHT_ROT,
};

void setup()
{
    // Initialize Arduino serial port (for display of ASCII output to PC)
    Serial.begin(115200);

}


void loop()
{
    uint16_t distance;
    uint8_t  c;
    DRIVE_FUNCTION driveMode = REST;

    // Continuous loop
    while (1)
    {
        // Each time through the loop, look for a serial input character
        if (Serial.available() > 0)
        {
            //  read input character ...
            c = (uint8_t) Serial.read();

            // ... and parse
            switch (c)
            {
                case 'S':
                case 's':
                    driveMode = STOP;
                    break;

                case 'R':
                case 'r':
                    driveMode = RIGHT_ROT;
                    break;

                case 'L':
                case 'l':
                    driveMode = LEFT_ROT;
                    break;

                case 'b':
                case 'B':
                    driveMode = BACKWARD;
                    break;

                case 'F':
                case 'f':
                    driveMode = FORWARD;
                    break;

                case 'Q':
                case 'q':
                    exit(3);
                    
                default:
                    Serial.println("=====================================");
                    Serial.println("== Type a single character command ==");
                    Serial.println("=====================================");
                    Serial.println(" S - Stop");
                    Serial.println(" B - Backwards");
                    Serial.println(" Q - Quit");
                    break;
            }
        }

        switch (driveMode)
        {
            case FORWARD:
                Serial.print("fwd\n");
                //fwd motor controller function
                break;

            case BACKWARD:
                Serial.print("reverse\n");
                //motor controller function
                break;

            case RIGHT_ROT:
                Serial.print("right\n");
                //motor controller function                
                break;

            case LEFT_ROT:
                Serial.print("left\n");
                //motor controller function
                break;

            case STOP:
                Serial.print("stop\n");
                //motor controller function
                break;
            default:
                Serial.print("default\n");
                //motor controller function
                break;
        }

        delay(100);
    }
}
