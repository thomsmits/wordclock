/*
 Main file for the clock control.
*/

/** 
  Number of LEDs and therefore output ports of the
  shift register cascade. */  
#define NUMBER_OF_LEDS 14*8

/** Enable debug output */
#define DEBUG_OUTPUT 1

/** Throttle the loop to an invocation every X milliseconds */
#define INTERVAL 100

/** Update the clock display every minute (60 seconds) */
#define LOOP_CLOCK (60000 / INTERVAL)

/** Update the brigthness every 0.5 seconds */
#define LOOP_BRIGHTNESS (500 / INTERVAL)

/** Check for the alarm on/off button 0.2 seconds */
#define LOOP_ALARM_TOGGLE (200 / INTERVAL)

/** Check for the setting 0.2 seconds */
#define LOOP_ALARM_SET (200 / INTERVAL)

/** Check for the alarm every 20 seconds */
#define LOOP_ALARM (20000 / INTERVAL)

/** 
  Set this macro if you want to have the south German way
  of indicating the time with "ES IST VIERTEL ZWOEFL" for 11:15
  and "ES IST DREIVIERTEL ZWOELF" for 11:45.
*/
//#define SOUTH_GERMAN_VERSION 1

// Trace macro for debugging output
#ifdef DEBUG_OUTPUT
#define trace(a) { Serial.print(a); }
#define tracenl(a) { Serial.print(a); Serial.print("\n"); }
#else
#define trace(a) 
#define tracenl(a) 
#endif

/**
  Initialize board. 
*/
void setup() {
#ifdef DEBUG_OUTPUT
  Serial.begin(9600);
#endif 

  hardware_initialize();
  
  // clock is booted freshly, allow
  // setting the time via the buttons
  set_dcf_time(12, 0, 0);
  show_current_time();
  adjust_brightness();
  set_time_by_button();
}

/**
 Board's main loop.
  
 The loop will be called by the hardware automatically
 as often as possible. As we do not need this speed, we
 will throttle it by delay() to an invocation every
 INTERVAL milliseconds. The different functions will not be
 called on every invocation but as defined by the
 corresponding constants LOOP_... A constant value of
 100 indicates that the function should be called on
 every 100th invocation of the loop, thus every 100 * INTERVAL
 milliseconds. 
*/
void loop(){ 

  static unsigned long loopCounter;
   
  if (loopCounter % LOOP_CLOCK == 0) {
    show_current_time();
  }
  
  if (loopCounter % LOOP_BRIGHTNESS == 0) {
    adjust_brightness();
  }
  
  if (loopCounter % LOOP_ALARM_TOGGLE == 0) {
    check_alarm_toggle();
  }
  
  if (loopCounter % LOOP_ALARM_SET == 0) {
    check_alarm_set();
  }
  
  if (loopCounter % LOOP_ALARM == 0) {
    check_alarm();
  }
  
  // add other clock functions here
  // ...
  
  delay(INTERVAL);
  loopCounter++; // wraparound intended
}



