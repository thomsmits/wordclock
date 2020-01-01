/*
 * Functions to handle real time clock attached to micro controller.
*/
#include <Wire.h>
#include <stdint.h>
#include "ports.h"

#include "rtc.h"

/* I2C Adresse of RTC  DS3231 */
#define RTC_I2C_ADDRESS 0x68

/**
 * Initialize the real time clock.
 */
void clock_initialize() {
  Wire.begin();
}

/**
 * Utility function to convert a decimal to a BCD value.
 *
 * @param val the decimal value to convert
 * @return the corresponding BCD value
 */
static uint8_t dec_to_bcd(uint8_t val) {
  return ((val / 10 * 16) + (val % 10));
}

/**
 * Utility function to convert a BCD value to a decimal value.
 *
 * @param val the BCD value to convert
 * @return the corresponding decimal value
 */
static uint8_t bcd_to_dec(uint8_t val) {
   return (uint8_t) ((val / 16 * 10) + (val % 16));
}

/**
 * Set the time of the RTC.
 *
 * @param hour hour
 * @param minute minute
 * @param second second
 * @param dayOfWeek day of the week
 * @param dayOfMonth day of the month
 * @param month month
 * @param year year
 */
static void set_rtc_time_internal(byte hour, byte minute, byte second, byte dayOfWeek, byte dayOfMonth, byte month, byte year) {
  Wire.beginTransmission(RTC_I2C_ADDRESS);
  Wire.write(0); /* set next input to start at the seconds register */
  Wire.write(dec_to_bcd(second)); /* set seconds */
  Wire.write(dec_to_bcd(minute)); /* set minutes */
  Wire.write(dec_to_bcd(hour)); /* set hours */
  Wire.write(dec_to_bcd(dayOfWeek)); /* set day of week (1=Sunday, 7=Saturday) */
  Wire.write(dec_to_bcd(dayOfMonth)); /* set date (1 to 31) */
  Wire.write(dec_to_bcd(month)); /* set month */
  Wire.write(dec_to_bcd(year)); /* set year (0 to 99) */
  Wire.endTransmission();
}

/**
 * Read the current time from the RTC chip.
 *
 * @param (out) hour hour
 * @param (out) minute minute
 * @param (out) second second
 */
void read_current_time(int* hour, int* minute, int* second) {

   Wire.beginTransmission(RTC_I2C_ADDRESS);
   Wire.write(0);
   Wire.endTransmission();
   Wire.requestFrom(RTC_I2C_ADDRESS, 7);

   *second = bcd_to_dec(Wire.read() & 0x7f);
   *minute = bcd_to_dec(Wire.read());
   *hour = bcd_to_dec(Wire.read() & 0x3f);

   trace("Time from RTC: "); trace(*hour); trace(":");
   trace(*minute); trace(":"); tracenl(*second);
}

/**
 * Manually set the RTC time.
 *
 * @param hour hour to set
 * @param minute minute to set
 * @param second second to set
 */
void set_rtc_time(int hour, int minute, int second) {
  set_rtc_time_internal(hour, minute, second, 1, 1, 1, 1);
}
