/* control for DC motor for brudh sweeper wtvr */

int in1 = 7; //Declaring the pins where in1 in2 from the driver are wired 
int in2 = 6;
void setup() {
  pinMode(in1, OUTPUT); //Declaring the pin modes, obviously they're outputs
  pinMode(in2, OUTPUT);
  }

void TurnMotorA(){             // TURNS IN RASH 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void TurnOFFA(){              // TURNS OUT FOR WHEN TRHAS BIN GOING DOWN 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void loop() {
  TurnMotorA(); //in the loop we use the function to turn the motor for 3s and stop it for 2s
  delay(3000);
  TurnOFFA();
  delay(2000);
}
