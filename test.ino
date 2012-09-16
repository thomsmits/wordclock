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
