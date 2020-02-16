enum State_enum {STOP, FORWARD, ROTATE_RIGHT, ROTATE_LEFT, REVERSE};
enum Camera_enum {NONE, OUT_RIGHT, OUT_LEFT, OUT, ON_TRACK};
 
void state_machine_run(uint8_t camera);
void motors_stop();
void motors_forward();
void motors_right();
void motors_left();
uint8_t read_Cam();
 
uint8_t state = STOP;
 
void setup(){
}
 
void loop(){
  state_machine_run(read_Cam());
 
  delay(10);
}
 
void state_machine_run(uint8_t camera) 
{
  switch(state)
  {
    case STOP:
      if(camera == NONE){
        motors_forward();
        state = FORWARD;
      }
      else if(camera == OUT_RIGHT){
        motors_left();
        state = ROTATE_LEFT;
      }
      else{
        motors_right();
        state = ROTATE_RIGHT;
      }
      break;
       
    case FORWARD:
      if(camera != NONE){
        motors_stop();
        state = STOP;
      }
      break;
 
    case ROTATE_RIGHT:
      if(camera == NONE || camera == OUT_RIGHT){
        motors_stop();
        state = STOP;
      }
      break;
 
    case ROTATE_LEFT:
      if(camera != OUT_RIGHT)
      {
        motors_stop();
        state = STOP; 
      }
      break;
  }
}
 
void motors_stop()
{
  //code for stopping motors
}
 
void motors_forward()
{
  //code for driving forward  
}
 
void motors_right()
{
  //code for turning right
}
 
void motors_left()
{
  //code for turning left
}
 
uint8_t read_Cam()
{
  //code for reading both sensors
}
