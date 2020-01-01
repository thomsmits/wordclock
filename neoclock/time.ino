/*
 * Time management functions.
 */
#include "time.h"

/**
 * Convert hour, minute and second to timestamp.
 *
 * @param hour hour
 * @param minute minute
 * @param second second
 * @param (out) timestamp in milliseconds
 */
void time_to_millis(int hour, int minute, int second, unsigned long* timestamp) {
  *timestamp = hour * MILLIS_PER_HOUR
      + minute * MILLIS_PER_MINUTE
      + second * MILLIS_PER_SECOND;
}

/**
 * Convert timestamp to hour, minute, second.
 *
 * @param timestamp timestamp in milliseconds
 * @param (out) hour hour
 * @param (out) minute minute
 * @param (out) second second
 */
void millis_to_time(unsigned long timestamp, int* hour, int* minute, int* second) {

  /* handle wraparound of day */
  while (timestamp > MILLIS_PER_DAY) {
    timestamp -= MILLIS_PER_DAY;
  }

  /* extract hour from timestamp */
  *hour = timestamp / MILLIS_PER_HOUR;

  /* remove hour part from timestamp */
  timestamp -= *hour * MILLIS_PER_HOUR;

  /* extract minute from timestamp */
  *minute = timestamp / MILLIS_PER_MINUTE;

  /* remove minute part from timestamp */
  timestamp -= *minute * MILLIS_PER_MINUTE;

  /* extract seconds from timestamp */
  *second = timestamp / MILLIS_PER_SECOND;
}

/**
 * Manage time wrap around on hour and minute.
 * If minute is > 60, hour is incremented.
 * If hour is > 24, it is set to hour =- 24.
 *
 * @param hour (in, out) hour
 * @param minute (int, out) minute
*/
void time_wrap(int* hour, int* minute) {
  while (*minute >= 60) {
    *minute -= 60;
    *hour++;
  }

  while (*hour >= 24) {
    *hour -= 24;
  }
}
