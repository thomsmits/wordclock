/*
 Functions for a primitive timer handling.
 
 THIS MODULE IS FAR FROM BEING FINISHED AND
 IS EXPERIMENTAL
*/

/**
  Function that should be executed periodically
  to ensure instant reaction of the clock to
  user input.
*/
void update() {
  
  // add all functions that need to be executed
  // periodically here
  check_alarm_interrupt_button();
}

/**
  Check the button to interrupt the alarm.
*/
static void check_alarm_interrupt_button() {
  int buttonState = digitalRead(PORT_BUTTON1);

  if (buttonState == HIGH) {
    stop_sound = true;   
  } 
}
  
