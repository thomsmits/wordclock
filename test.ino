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

void test_shift_register() {
  int ledBits[NUMBER_OF_LEDS];
  
  ledBits[NUMBER_OF_LEDS - 1] = 1;  
  send_to_shift_registers(ledBits);

  ledBits[NUMBER_OF_LEDS - 2] = 1;  
  send_to_shift_registers(ledBits);

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

}
