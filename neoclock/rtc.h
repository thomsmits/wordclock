/*
 * Functions to handle real time clock attached to micro controller.
*/
#include <Wire.h>
#include <stdint.h>
#include "ports.h"

#ifndef __rtc_h__
#define __rtc_h__

/**
 * Initialize the real time clock.
 */
void clock_initialize();

/**
 * Read the current time from the RTC chip.
 *
 * @param (out) hour hour
 * @param (out) minute minute
 * @param (out) second second
 */
void read_current_time(int* hour, int* minute, int* second);

/**
 * Manually set the RTC time.
 *
 * @param hour hour to set
 * @param minute minute to set
 * @param second second to set
 */
void set_rtc_time(int hour, int minute, int second);

#endif