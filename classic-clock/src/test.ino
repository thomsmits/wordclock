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
  trace(hour);
  trace(":");
  trace(minute);
  trace(":");
  trace(second);
  trace("\n");
}

/**
  Function to cycle through some times for testing purpose.
  */
static void test_display() {
  
  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
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
    delay(2000);
  }
  
  // test hour display
  for (int hour = 0; hour < 24; hour += 1) {
    set_dcf_time(hour, 15, 0);
    read_current_time(&hour, &minute, &second);
    display_time(hour, minute, ledBits);
    send_to_shift_registers(ledBits);
    dbg_output_time(hour, minute, second);
    delay(2000);
  }
}

/**
  Test playing some simple sounds.
  */
void test_play_melody() {
 loop_melody(BEEP_MELODY, BEEP_BEATS, 10, 500); 
 loop_melody(SMB_MELODY, SMB_BEATS, 2, 500);
}

/**
  Test the DCF clock.
*/
void test_dcf_clock() {
  
  int hour, minute, second;
 
  set_dcf_time(16, 42, 23);
  acquire_dcf_time();
  read_current_time(&hour, &minute, &second);
  dbg_output_time(hour, minute, second);
}

/**
 Test some values for dimming the clock via PWM.
 
 The method goes from the lowest possible brightness
 to full brightness.
 
 @param pauseMs time in milliseconds to keep each 
        brightness value before moving to the next.
*/
void test_pwm_dimming(unsigned long pauseMs) {
  
  set_brightness(1);
  delay(pause);
    
  set_brightness(2);
  delay(pause);
  
  set_brightness(4);
  delay(pause);
  
  set_brightness(8);
  delay(pause);
  
  set_brightness(16);
  delay(pause);

  set_brightness(32);
  delay(pause);

  set_brightness(64);
  delay(pause);

  set_brightness(128);
  delay(1000);

  set_brightness(256);
  delay(pause);
}

/**
 Turn on the first LED, wait some time, turn off the first
 and turn on the second and so on...
 
 @param delayMs time in milliseconds to wait before moving to
        the next LED.
*/
void test_runlight(int delayMs) {
  
  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
  
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    ledBits[i] = 1;
    send_to_shift_registers(ledBits);
    delay(delayMs);
    ledBits[i] = 0;
  }
}


/**
 Turn on one dedicated LED, indicated by the index.
 
 @param index index of the LED to test (< NUMBER_OF_LEDs).
*/
void test_turn_on_led(int index) {
  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
  
  ledBits[index] = 1;
  send_to_shift_registers(ledBits);
}



void test_new_board_odd() {
  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
  
  for (int i = 0; i < NUMBER_OF_LEDS; i += 2) {
    ledBits[i] = 1;
  }
  send_to_shift_registers(ledBits);

}

void test_new_board_even() {

  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
  
  for (int i = 1; i < NUMBER_OF_LEDS; i += 2) {
    ledBits[i] = 1;
  }
  send_to_shift_registers(ledBits);
}

void test_all_led_on() {
  
  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
  
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    ledBits[i] = 1;
  }
  
  send_to_shift_registers(ledBits);
}

void test_all_led_off() {
  
  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
  
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    ledBits[i] = 0;
  }
  
  send_to_shift_registers(ledBits);
}


void test_font_display() {

  int ledBits[NUMBER_OF_LEDS];

  for (int i = 0; i < 10; i++) {
    memfill(ledBits, NUMBER_OF_LEDS, 0);
    print_char_8x8(ledBits, 0, 0, '0' + i);
    send_to_shift_registers(ledBits);
    delay(500);
  }
  
  for (int i = 0; i < 27; i++) {
    memfill(ledBits, NUMBER_OF_LEDS, 0);
    print_char_8x8(ledBits, 0, 0, 'A' + i);
    send_to_shift_registers(ledBits);
    delay(500);
  }
  
  
}

