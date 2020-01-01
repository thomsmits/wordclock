/*
 * Time management functions.
 */
#ifndef __time_h__
#define __time_h__

#define MILLIS_PER_DAY (24L*60*60*1000)
#define MILLIS_PER_HOUR (60L*60*1000)
#define MILLIS_PER_MINUTE (60L*1000)
#define MILLIS_PER_SECOND (1000L)

/**
 * Convert hour, minute and second to timestamp.
 *
 * @param hour hour
 * @param minute minute
 * @param second second
 * @param (out) timestamp in milliseconds
 */
void time_to_millis(int hour, int minute, int second, unsigned long* timestamp);

/**
 * Convert timestamp to hour, minute, second.
 *
 * @param timestamp timestamp in milliseconds
 * @param (out) hour hour
 * @param (out) minute minute
 * @param (out) second second
 */
void millis_to_time(unsigned long timestamp, int* hour, int* minute, int* second);

/**
 * Manage time wrap around on hour and minute.
 * If minute is > 60, hour is incremented.
 * If hour is > 24, it is set to hour =- 24.
 *
 * @param hour (in, out) hour
 * @param minute (int, out) minute
*/
void time_wrap(int* hour, int* minute);

#endif