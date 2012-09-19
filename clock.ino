/*
 Main file for the clock control.
*/


/** 
  Number of LEDs and therefore output ports of the
  shift register cascade. */  
#define NUMBER_OF_LEDS 14*8

/**
  Initialize board. 
*/
void setup() {
  Serial.begin(9600);
  hardware_initialize();
}

/**
  Board's main loop.
*/
void loop(){ 
  test_runlight(100);
test_all_led_on();
delay(10000);
 /*
  test_new_board_even();
  delay(1000);
  test_new_board_odd();
  delay(1000);

  test_runlight();
  
  test_all_led_on();
  delay(1000);
  
  test_pwm();
 
*/

  //test_runlight(100);
  
// test_new_board_odd();
 
// test_all_led_on();
  //delay(10000);
  /*
  
  
  return;
   
   test_all_led_on();
   
   delay(10000);
  // test_all_led_off();
   
  // delay(2000);
  
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

 //test_new_board_odd();
 
 // test_new_board_even();
 //delay(1000000);
  
//  test_new_board_even();
  //test_all_led_on();
  //test_pwm();
  
//write_to_port(3, HIGH);
//write_to_port(3, LOW);

 //test_new_board_even();
//test_runlight();



  //
  
  
 // test_single_led();
 //test_runlight();
 // delay(1000000);
 //test_turn_on_led(111);
 //delay(200);
 //test_turn_off_led(111);
 //delay(200);
 */
}


