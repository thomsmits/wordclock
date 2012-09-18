/**
  Initialize board. 
*/
void setup() {
  hardware_initialize();
  Serial.begin(9600);
  beep();
  //test_shift_register();
}


/**
  Board's main loop.
*/
void loop(){ 
  
  
  
  //int brightness = get_ambient_brightness();
  //int ledBrightness = max(255 - brightness, 1);
  //set_brightness(ledBrightness);
  //test_play_melody();
  //update();
  //test_display();
  
  //test_shift_register();
  //test_pwm();
  //test_dcf_clock();
  //delay(100);

//  test_new_board_add();
  
  /*
  test_new_board_even();
  delay(1000);
  test_new_board_odd();
  delay(1000);
*/
  test_new_board_all();
 // test_single_led();
 // test_runlight();
 // delay(1000000);
}

