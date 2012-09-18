/*
  Debugging und testing functions.
*/


/**
  Debugging function to write current time on serial output.
  
  @param hour hour 
  @param minute minute 
  @param second second
*/  
static void dbg_output_time(int hour, int minute, int second) {
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
  Serial.print("\n");
}

/**
  Function to cycle through some times for testing purpose.
  */
static void test_display() {
  
  int ledBits[NUMBER_OF_LEDS];
  int hour;
  int minute;
  int second;
  
  // test minute display
  for (int minute = 0; minute < 60; minute += 5) {
    set_dcf_time(11, minute, 0);
    read_current_time(&hour, &minute, &second);
    display_time(hour, minute, ledBits);
    send_to_shift_registers(ledBits);
    dbg_output_time(hour, minute, second);
  }
  
  // test hour display
  for (int hour = 0; hour < 24; hour += 1) {
    set_dcf_time(hour, 15, 0);
    read_current_time(&hour, &minute, &second);
    display_time(hour, minute, ledBits);
    dbg_output_time(hour, minute, second);
  }
  
  alarm_time_increment();
}

void test_play_melody() {
 loop_melody(BEEP_MELODY, BEEP_BEATS, 10, 500); 
 loop_melody(SMB_MELODY, SMB_BEATS, 2, 500);
}

void test_dcf_clock() {
  
  int hour, minute, second;
 
  set_dcf_time(16, 42, 23);
  acquire_dcf_time();
  read_current_time(&hour, &minute, &second);
  dbg_output_time(hour, minute, second);
}

void test_pwm() {

  /*set_brightness(100);
  delay(1500);
  
  set_brightness(75);
  delay(1500);
  
  set_brightness(50);
  delay(1500);
  
  set_brightness(25);
  delay(1500);
  
  set_brightness(5);
  delay(1500);
  
  */
  
  set_brightness(1);
  delay(1500);
    
  set_brightness(2);
  delay(1500);
  
  set_brightness(4);
  delay(1500);
  
  
  set_brightness(8);
  delay(1500);
  
  set_brightness(16);
  delay(1500);

  set_brightness(32);
  delay(1500);

  set_brightness(64);
  delay(1500);

  set_brightness(128);
  delay(1500);

  set_brightness(256);
  delay(1500);

  
  set_brightness(0);
  delay(1500);
 /*
  analogWrite(PORT_OUTPUT_ENABLE, 255);
  delay(1500);
  
  analogWrite(PORT_OUTPUT_ENABLE, 254);
  delay(1500);
  
  analogWrite(PORT_OUTPUT_ENABLE, 240);
  delay(1500);

  analogWrite(PORT_OUTPUT_ENABLE, 190);
  delay(1500);

  analogWrite(PORT_OUTPUT_ENABLE, 150);
  delay(1500);

  analogWrite(PORT_OUTPUT_ENABLE, 125);
  delay(1500);

  analogWrite(PORT_OUTPUT_ENABLE, 100);
  delay(1500);
  
  analogWrite(PORT_OUTPUT_ENABLE, 50);
  delay(1500);
  
  analogWrite(PORT_OUTPUT_ENABLE, 0);
  delay(1500);
  

  analogWrite(PORT_OUTPUT_ENABLE, 1);
  delay(500);
  analogWrite(PORT_OUTPUT_ENABLE, 0);
  delay(1500);
  */
  
 

  
  //digitalWrite(PORT_OUTPUT_ENABLE, LOW);
  //digitalWrite(PORT_OUTPUT_ENABLE, HIGH);
  //delayMicroseconds(del);
  
/*
  del += 1000;
  
  
  for (int i = 0; i < 10; i++) {
    digitalWrite(PORT_OUTPUT_ENABLE, LOW);
    delayMicroseconds(del);
    digitalWrite(PORT_OUTPUT_ENABLE, HIGH);
    delayMicroseconds(del);
  }
  
  if (del == 1000) {
    del = 0;
  }
*/
}
  
void test_runlight() {
  
  int ledBits[NUMBER_OF_LEDS];
    
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    ledBits[i] = 1;
    send_to_shift_registers(ledBits);
    delay(100);
    ledBits[i] = 0;
  }
}

void test_single_led() {
  int ledBits[NUMBER_OF_LEDS];
  ledBits[NUMBER_OF_LEDS - 1] = 1;  
  send_to_shift_registers(ledBits);
}

void test_shift_register() {
  int ledBits[NUMBER_OF_LEDS];
  
  for (int i = 0; i < NUMBER_OF_LEDS; i += 1) {
    ledBits[i] = 1;
  }
  
  send_to_shift_registers(ledBits);
  /*
  delay(1000);
 
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    ledBits[NUMBER_OF_LEDS] = 0;
  }
  
  send_to_shift_registers(ledBits);
  
  delay(1000);
 */
  /*
  ledBits[NUMBER_OF_LEDS - 1] = 1;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 2] = 1;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 3] = 0;  
  send_to_shift_registers(ledBits);
 */
 /* 
  for (int i = 1; i < 10; i++) {
    ledBits[NUMBER_OF_LEDS - i] = 1;  
  }
  send_to_shift_registers(ledBits);
  */
/*
  ledBits[NUMBER_OF_LEDS - 3] = 1;  
  send_to_shift_registers(ledBits);

  ledBits[NUMBER_OF_LEDS - 4] = 1;  
  send_to_shift_registers(ledBits);

  ledBits[NUMBER_OF_LEDS - 5] = 1;  
  send_to_shift_registers(ledBits);

  ledBits[NUMBER_OF_LEDS - 6] = 1;  
  send_to_shift_registers(ledBits);

  ledBits[NUMBER_OF_LEDS - 7] = 1;  
  send_to_shift_registers(ledBits);

  ledBits[NUMBER_OF_LEDS - 8] = 1;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 9] = 1;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 9] = 0;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 8] = 0;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 7] = 0;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 6] = 0;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 5] = 0;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 4] = 0;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 3] = 0;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 2] = 0;  
  send_to_shift_registers(ledBits);
  
  ledBits[NUMBER_OF_LEDS - 1] = 0;  
  send_to_shift_registers(ledBits);
*/
}


void test_new_board_odd() {
  int ledBits1[NUMBER_OF_LEDS];
  
  for (int i = 0; i < NUMBER_OF_LEDS; i += 2) {
    ledBits1[i] = 1;
  }
  send_to_shift_registers(ledBits1);

  Serial.print("Ungerade LEDs an!\n");
}

void test_new_board_even() {

  int ledBits2[NUMBER_OF_LEDS];
  for (int i = 1; i < NUMBER_OF_LEDS; i += 2) {
    ledBits2[i] = 1;
  }
  send_to_shift_registers(ledBits2);
 
  Serial.print("Gerade LEDs an!\n");
}

void test_new_board_all() {

  int ledBits[NUMBER_OF_LEDS];
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    ledBits[i] = 1;
  }
  send_to_shift_registers(ledBits);
 
  Serial.print("Alle LEDs an!\n");
  
  delay(15000); 
}
