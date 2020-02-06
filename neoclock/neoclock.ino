/*
 Main file for the clock control.
*/
#include <stdint.h>

#include "display.h"
#include "hardware.h"
#include "rtc.h"
#include "ambientlight.h"

/** Enable debug output */
#define DEBUG_OUTPUT 1

/** Test the clock */
#undef TESTMODE

#ifdef TESTMODE
  #define DEBUG_OUTPUT 1
#endif

/** Trace macros */
#include "trace.h"

/** Throttle the loop to an invocation every X milliseconds */
#define INTERVAL 100

/** Update the clock display every minute (10 seconds) */
#define LOOP_CLOCK (10000 / INTERVAL)

/** Check for a color change button press */
#define LOOP_COLOR_CYCLE (200 / INTERVAL)

/** Check for the hour or minute button */
#define LOOP_TIME_CHANGE (200 / INTERVAL)

/** Check for changes of the ambient light */
#define LOOP_AMBIENT_LIGHT_CHANGE (200 / INTERVAL)

/**
 * Set this macro if you want to have the south German way
 * of indicating the time with "ES IST VIERTEL ZWOEFL" for 11:15
 * and "ES IST DREIVIERTEL ZWOELF" for 11:45.
*/
/*
#define SOUTH_GERMAN_VERSION 1
*/

/**
  Initialize board.
*/
void setup() {
#ifdef DEBUG_OUTPUT
  Serial.begin(115200);
#endif

  hardware_initialize();
  clock_initialize();
  show_current_time();
}

/**
 * Board's main loop.
 *
 * The loop will be called by the hardware automatically
 * as often as possible. As we do not need this speed, we
 * will throttle it by delay() to an invocation every
 * INTERVAL milliseconds. The different functions will not be
 * called on every invocation but as defined by the
 * corresponding constants LOOP_... A constant value of
 * 100 indicates that the function should be called on
 * every 100th invocation of the loop, thus every 100 * INTERVAL
 * milliseconds.
 */
void loop(){

#ifdef TESTMODE
  show_all_words();
  show_all_times_and_colors();
#else
  static unsigned long loopCounter;

  /* read light sensor */
  if (loopCounter % LOOP_AMBIENT_LIGHT_CHANGE == 0) {
    dim = get_ambient_brightness();
    if (dim < 0.01) {
      dim = 0.01;
    }
  }

  /* Time update */
  if (loopCounter % LOOP_CLOCK == 0) {
    show_current_time();
  }

  /* color change */
  if (loopCounter % LOOP_COLOR_CYCLE == 0) {
    if (check_color_change()) {
      /* color was changed - redraw time */
      show_current_time();
    }
  }

  /* time change */
  if (loopCounter % LOOP_TIME_CHANGE == 0) {
    if (check_time_change()) {
      /* time was changed - redraw time */
      show_current_time();
    }
  }

  /* add other clock functions here
     ...
  */

  delay(INTERVAL);
  loopCounter++; /* wrap-around intended */
#endif
}

/**
 * Debugging function to write current time on serial output.
 *
 * @param hour hour
 * @param minute minute
 * @param second second
 */
static void dbg_output_time(int hour, int minute, int second) {
  trace(hour);
  trace(":");
  trace(minute);
  trace(":");
  trace(second);
  trace("\n");
}
