/**
  Initialize board. 
*/
void setup() {
  hardware_initialize();
  Serial.begin(9600);
  beep();
}

/**
  Board's main loop.
*/
void loop(){ 
  
  //test_play_melody();
  //update();
  //test_display();
  
  test_shift_register();
  //test_dcf_clock();
  delay(100);
}

