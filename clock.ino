/**
  Initialize board. 
*/
void setup() {
  hardware_initialize();
  Serial.begin(9600);
}

/**
  Board's main loop.
*/
void loop(){ 
  test_display();
  delay(100000);
}

