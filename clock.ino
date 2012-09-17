/**
  Initialize board. 
*/
void setup() {
  hardware_initialize();
  Serial.begin(9600);
  beep();
  test_shift_register();
}


/**
  Board's main loop.
*/
void loop(){ 
  
  //test_pwm();
  int brightness = get_ambient_brightness();
  int ledBrightness = max(255 - brightness, 1);
  set_brightness(ledBrightness);
  //test_play_melody();
  //update();
  //test_display();
  
  //test_shift_register();
  //test_dcf_clock();
  //delay(100);
}

