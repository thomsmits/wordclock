/**
 * Displaying information on the LED panel/stripe.
 */
#include <string.h>

#include "trace.h"
#include "hardware.h"
#include "display.h"
#include "rtc.h"

/**
 * Sets the bits in resultArray depending on the values of the
 * arrayToAdd. Bits already set in the input array will not
 * be set to zero.
 *
 * WARNING: this function does not perform any bounds checks!
 *
 * @param arrayToAdd Array containing the bits to be set as
 *        index of the bit. The value 5 for example implies
 *        that the 6th bit in the resultArray has to be set to 1.
 *        This array has to be terminated by -1.
 *
 * @param (out) ledBits Array where the bits will be set according
 *        to the input array. The ledBits has to be big enough to
 *        accommodate the indices provided in arrayToAdd.
 */
static void compose(const uint8_t arrayToAdd[], uint8_t ledBits[]) {
  int pos;
  int i = 0;

  while ((pos = arrayToAdd[i++]) != 0xff) {
    ledBits[pos] = 1;
  }
}

/**
 * Compose the hour information for the clock.
 *
 * @param displayHour the hour to be shown. Because of the fact that 8:30 is
 *        spelled out as "HALB NEUN", this value can deviate from the
 *        hour. In the example 8:30 hour is 8 but displayHour is 9
 * @param minute the minute, required to distinguish between the singular and
 *        plural for the first hour "EIN" versus "EINS"
 * @param (out) ledBits array to set led bits
 */
static void compose_hour(const int displayHour, const int minute, uint8_t ledBits[]) {

  int hourAMPM = displayHour;

  if (displayHour >= 12) {
    hourAMPM -= 12;
  }

  trace("display_hour: ");
  trace("displayHour=");
  trace(displayHour);
  trace(", hourAMPM=");
  tracenl(hourAMPM);

  /* compose the hour information */
  switch (hourAMPM) {

    case 0:
      compose(ZWOELF, ledBits);
      break;

    case 1:
      if (minute == 0) {
        compose(EIN, ledBits);
      }
      else {
        compose(EINS, ledBits);
      }
      break;

    case 2:
      compose(ZWEI, ledBits);
      break;

    case 3:
      compose(DREI, ledBits);
      break;

    case 4:
      compose(VIER, ledBits);
      break;

    case 5:
      compose(FUENF, ledBits);
      break;

    case 6:
      compose(SECHS, ledBits);
      break;

    case 7:
      compose(SIEBEN, ledBits);
      break;

    case 8:
      compose(ACHT, ledBits);
      break;

    case 9:
      compose(NEUN, ledBits);
      break;

    case 10:
      compose(ZEHN, ledBits);
      break;

    case 11:
      compose(ELF, ledBits);
      break;

    case 12:
      compose(ZWOELF, ledBits);
      break;
  }
}

/**
  * Displays hour and minutes on the LED panel.
  *
  * @param hour the hour to be set
  * @param minute the minute to be set
  * @param (out) ledBits bits for the LEDs (will NOT be cleared)
  */
static void display_time(const int hour, const int minute, uint8_t ledBits[]) {

  int roundMinute = (minute / 5) * 5;
  int remainingMinute = minute - roundMinute;

  trace("display_time: ");
  trace("roundMinute=");
  trace(roundMinute);

  int displayHour = hour;

  switch (roundMinute) {
    case 0:
      compose(UHR, ledBits);
      tracenl(", case 0");
      break;

    case 5:
      compose(FUENF_M, ledBits);
      compose(NACH, ledBits);
      tracenl(", case 5");
      break;

    case 10:
      compose(ZEHN_M, ledBits);
      compose(NACH, ledBits);
      tracenl(", case 10");
      break;

#ifdef SOUTH_GERMAN_VERSION
    case 15:
      compose(VIERTEL, ledBits);
      displayHour++;
      tracenl(", case 15-sg");
      break;
#else
    case 15:
      compose(VIERTEL, ledBits);
      compose(NACH, ledBits);
      tracenl(", case 15-!nsg");
      break;
#endif

    case 20:
      compose(ZWANZIG, ledBits);
      compose(NACH, ledBits);
      tracenl(", case 20");
      break;

    case 25:
      compose(FUENF_M, ledBits);
      compose(VOR, ledBits);
      compose(HALB, ledBits);
      displayHour++;
      tracenl(", case 25");
      break;

    case 30:
      compose(HALB, ledBits);
      displayHour++;
      tracenl(", case 30");
      break;

    case 35:
      compose(FUENF_M, ledBits);
      compose(NACH, ledBits);
      compose(HALB, ledBits);
      displayHour++;
      tracenl(", case 35");
      break;

    case 40:
      compose(ZWANZIG, ledBits);
      compose(VOR, ledBits);
      displayHour++;
      tracenl(", case 40");
      break;

#ifdef SOUTH_GERMAN_VERSION
    case 45:
      compose(DREIVIERTEL, ledBits);
      displayHour++;
      tracenl(", case 45-sg");
      break;
#else
    case 45:
      compose(VIERTEL, ledBits);
      compose(VOR, ledBits);
      displayHour++;
      tracenl(", case 45-!sg");
      break;
#endif

    case 50:
      compose(ZEHN_M, ledBits);
      compose(VOR, ledBits);
      displayHour++;
      tracenl(", case 50");
      break;

    case 55:
      compose(FUENF_M, ledBits);
      compose(VOR, ledBits);
      displayHour++;
      tracenl(", case 55");
      break;

    default:
      tracenl(", default-case");
  }

  /* Light dots for exact minute */
  switch (remainingMinute) {
    /* Fall through is intended!!! */
    case 4:
      compose(MIN_4, ledBits);

    case 3:
      compose(MIN_3, ledBits);

    case 2:
      compose(MIN_2, ledBits);

    case 1:
      compose(MIN_1, ledBits);
  }

  /* AM/PM indicator */
  if (hour >= 12) {
    compose(PM, ledBits);
  }

  compose_hour(displayHour, roundMinute, ledBits);

  send_to_leds(ledBits);
}

/**
 * Show the current time on the display of the clock. The time is
 * acquired from the RTC.
 */
void show_current_time() {

  int hour;
  int minute;
  int second;

  uint8_t ledBits[NUMBER_OF_LEDS];
  memset(ledBits, 0, NUMBER_OF_LEDS);

  read_current_time(&hour, &minute, &second);

  compose(ES, ledBits);
  compose(IST, ledBits);

  display_time(hour, minute, ledBits);

  dbg_output_time(hour, minute, second);
}
