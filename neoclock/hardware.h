/*
 * Functions to handle the hardware of the clock if it
 * is based on Neopixel strips.
 */
#include <stdint.h>
#include <stdbool.h>

#ifndef __hardware_h__
#define __hardware_h__

/* Value to dim the stripe in general */
double dim = 1.0;

/* Maximum values for hour and minute */
#define MAX_HOUR 23
#define MAX_MINUTE 59

/**Number of LEDs in the Neopixel stripe */
#define NUMBER_OF_LEDS 130

/* Color values */
typedef struct {
  int r;
  int g;
  int b;
} Color;

/* Size of the color pallette */
/* TODO: Move to other file, does not belong here */
#define PALETTE_SIZE 17

/* Color palette to cycle through */
Color palette[PALETTE_SIZE] = {
  /* greyscale */
  { 0xff, 0xff, 0xff },
  { 0x7f, 0x7f, 0x7f },
  { 0x3f, 0x3f, 0x3f },
  { 0x1f, 0x1f, 0x1f },
  { 0x0f, 0x0f, 0x0f },

  /* orange */
  { 0xff, 0x8f, 0x00 },
  { 0xa1, 0x5a, 0x00 },
  { 0x56, 0x30, 0x00 },

  /* green */
  { 0x00, 0xff, 0x00 },
  { 0x00, 0x3f, 0x00 },
  { 0x00, 0x1f, 0x00 },

  /* blue */
  { 0x00, 0x65, 0xff },
  { 0x00, 0x30, 0x79 },
  { 0x00, 0x19, 0x30 },

  /* red */
  { 0xff, 0x00, 0x00 },
  { 0x3f, 0x00, 0x00 },
  { 0x1f, 0x00, 0x00 },
};

/**
  * Positions of the text on the LED stripe.
  *
  * As the Arduino programming language (C) cannot determine
  * the length of an array that is passed to a function
  * as a pointer, a 0xFF at the end of the array indicates the
  * end of the array.
  *
  * The range of the values in the array have to be < NUMBER_OF_LEDS.
 */
const uint8_t ES[]          = { 103, 104, 0xff };
const uint8_t IST[]         = { 106, 107, 108, 0xff };
const uint8_t FUENF_M[]     = { 110, 111, 112, 113, 0xff };
const uint8_t ZEHN_M[]      = { 102, 101, 100, 99, 0xff };
const uint8_t ZWANZIG[]     = { 98, 97, 96, 95, 94, 93, 92, 0xff };
const uint8_t DREIVIERTEL[] = { 81, 82, 83, 84, 85, 86, 87, 88, 89 ,90, 91, 0xff };
const uint8_t VIERTEL[]     = { 85, 86, 87, 88, 89, 90, 91, 0xff };
const uint8_t VOR[]         = { 74, 73, 72, 0xff };
const uint8_t NACH[]        = { 78, 77, 76, 75, 0xff };
const uint8_t HALB[]        = { 59, 60, 61, 62, 0xff };
const uint8_t ELF[]         = { 34, 35, 36, 0xff };
const uint8_t EIN[]         = { 56, 55, 54, 0xff };
const uint8_t EINS[]        = { 56, 55, 54, 53, 0xff };
const uint8_t ZWEI[]        = { 58, 57, 56, 55, 0xff };
const uint8_t DREI[]        = { 38, 39, 40, 41, 0xff };
const uint8_t FUENF[]       = { 44, 45, 46, 47, 0xff };
const uint8_t VIER[]        = { 26, 27, 28, 29, 0xff };
const uint8_t SECHS[]       = { 9, 10, 11, 12, 13, 0xff };
const uint8_t ACHT[]        = { 16, 17, 18, 19, 0xff };
const uint8_t SIEBEN[]      = { 53, 52, 51, 50, 49, 48, 0xff };
const uint8_t ZWOELF[]      = { 64, 65, 66, 67, 68, 0xff };
const uint8_t ZEHN[]        = { 20, 21, 22, 23, 0xff };
const uint8_t UHR[]         = { 4, 5, 6, 0xff };
const uint8_t NEUN[]        = { 30, 31, 32, 33, 0xff };
const uint8_t PM[]          = { 115, 0xff };
const uint8_t WECKER[]      = { 114, 0xff };
const uint8_t MIN_1[]       = { 0, 0xff };
const uint8_t MIN_2[]       = { 1, 0xff };
const uint8_t MIN_3[]       = { 2, 0xff };
const uint8_t MIN_4[]       = { 3, 0xff };

/**
 * Cycle through the color palette.
 */
void cycle_color();

/**
 * Clear all pixel, i.e. set them to black.
 */
void clear();

/**
 * Initialize hardware.
 */
void hardware_initialize();

/**
 * Sends the given bit pattern to the LEDs.
 *
 * @param ledBits the bit pattern to be sent. The length of the array
 *       has to be as defined in NUMBER_OF_LEDS. No bounds check performed!
 */
void send_to_leds(const uint8_t ledBits[]);

/**
 * Sends the given bit pattern to the LEDs.
 *
 * @param ledBits the bit pattern to be sent. The length of the array
 *       has to be as defined in NUMBER_OF_LEDS. No bounds check performed!
 */
void send_to_leds(const uint8_t ledBits[]);

/**
 * Check whether the color change button was pressed.
 *
 * @return true if there was a change of color, otherwise false
 */
bool check_color_change();

/**
 * Check if the buttons for setting the time were pressed.
 *
 * @return true if there was a change of time, otherwise false
 */
bool check_time_change();

#endif
