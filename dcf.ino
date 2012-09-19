/*
  DCF clock functions.
*/
#include <DCF77.h>
#define PORT_DCF 7

/** Arduino timestamp at last DCF update */
static unsigned long millis_at_last_dcf;

/** Last DCF time as timestamp */
static unsigned long dcf_millis;

/** Class to access DCF time from external receiver */
DCF77 myDCF = DCF77(PORT_DCF);

/**
  Return the internal timestamp at last DCF update.
*/
unsigned long get_millis_at_last_dcf() {
  return millis_at_last_dcf;
}

/**
  Return timestamp deliverd by DCF clock at last update.
*/
unsigned long get_dcf_millis() {
  return dcf_millis;
}

/**
  Get the current DCF time from the DCF clock and
  update corresponding global variables.
*/
void acquire_dcf_time() {
  // TODO: commented out until the clock is attached to the board
  /*
  int DCFsignal = myDCF.scanSignal();
  
  if (DCFsignal) {
    //beep();
    digitalWrite(13, HIGH);
  
    int hour   = myDCF.hh;
    int minute = myDCF.mm;
    int second = myDCF.ss;
    
    if (hour != 0 && minute != 0 && second != 0) {
      time_to_millis(hour, minute, second, &dcf_millis);
      millis_at_last_dcf = millis();  
    }
  }
  else {
    Serial.print("No Signal!");
    digitalWrite(13, LOW);
  }
  */
}

/**
  Manually set the DCF time (for testing purpose).
 
 @param hour hour to set
 @param minute minute to set
 @param second second to set
 */
static void set_dcf_time(int hour, int minute, int second) {
  time_to_millis(hour, minute, second, &dcf_millis);
}

/**
  Reads the internal Arduino timer, corrects it with the last time
  acquired from the DCF clock and returns it.
  
  @param (out) hour hour
  @param (out) minute minute
  @param (out) second second
*/ 
void read_current_time(int* hour, int* minute, int* second) {
  unsigned long timeInMillis = millis();
  unsigned long diff = timeInMillis - get_millis_at_last_dcf();
  unsigned long currentMillis = get_dcf_millis() + diff;
  
  millis_to_time(currentMillis, hour, minute, second);  
}


