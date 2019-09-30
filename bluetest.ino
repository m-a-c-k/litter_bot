#define ledPin 7
int state = 0;

void setup() {
  Serial.begin(38400);  
  // put your setup code here, to run once:

}

void loop() {
  if (true) {
    state = Serial.read();
    Serial.println(state);
    // put your main code here, to run repeatedly:
  }

}
