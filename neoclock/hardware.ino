/*
 * Functions to handle the hardware of the clock if it
 * is based on Neopixel strips.
 */
#include <FastLED.h>
#include <string.h>

#include "ports.h"

/* Value to dim the stripe in general */
#define DIM 1.0

/* Maximum values for hour and minute */
#define MAX_HOUR 23
#define MAX_MINUTE 59

/* Color values */
typedef struct {
  int r;
  int g;
  int b;
} Color;

/* Initialize data structure for FastLED-Library */
CRGB leds[NUMBER_OF_LEDS];

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

/* Current color of the clock */
static Color current_color = palette[0];
static int current_color_index = 0;

/**
 * Cycle through the color palette.
 */
void cycle_color() {

  current_color_index++;

  if (current_color_index >= PALETTE_SIZE) {
    current_color_index = 0;
  }

  current_color = palette[current_color_index];

  trace("Color changed to index=");
  trace(current_color_index);
  trace(", rgb={");
  trace(current_color.r); trace(", ");
  trace(current_color.g); trace(", ");
  trace(current_color.b); tracenl("}");
}

/**
 * Clear all pixel, i.e. set them to black.
 */
void clear() {
  /* set all pixel to black */
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.show();
}

/**
 * Initialize hardware.
 */
void hardware_initialize() {
  /* Configure pins of microcontroller */
  pinMode(PORT_BUTTON1, INPUT_PULLDOWN);
  pinMode(PORT_BUTTON2, INPUT_PULLDOWN);
  pinMode(PORT_BUTTON3, INPUT_PULLDOWN);

  /* Initialize the library */
  FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL>(leds, NUMBER_OF_LEDS);

  /* start with all pixels black */
  clear();
}

/**
 * Sends the given bit pattern to the LEDs.
 *
 * @param ledBits the bit pattern to be sent. The length of the array
 *       has to be as defined in NUMBER_OF_LEDS. No bounds check performed!
 */
void send_to_leds(const uint8_t ledBits[]) {

  trace("send_to_leds: color={ ");
  trace(current_color.r);
  trace(", ");
  trace(current_color.g);
  trace(", ");
  trace(current_color.b);
  tracenl(" }");

  for (int i = 0; i < NUMBER_OF_LEDS; i++) {

    if (ledBits[i] == 1) {
      /* LED is on */

      /* set pixel to the given color */
      leds[i].r = (int) (current_color.r * DIM);
      leds[i].g = (int) (current_color.g * DIM);
      leds[i].b = (int) (current_color.b * DIM);

      trace("LED[") trace(i);
      trace("]={"); trace(leds[i].r);
      trace(", ");  trace(leds[i].g);
      trace(", ");  trace(leds[i].b);
      tracenl(" }");
    }
    else {
      /* LED is off */
      leds[i] = CRGB::Black;
    }
  }

  /* display result */
  FastLED.show();
}

/**
 * Check whether the color change button was pressed.
 *
 * @return true if there was a change of color, otherwise false
 */
bool check_color_change() {

  int btn1, btn2, btn3;
  poll_buttons(&btn1, &btn2, &btn3);

  if (btn3 == HIGH) {

    /* wait until button is released again */
    while (btn3 == HIGH) {
      poll_buttons(&btn1, &btn2, &btn3);
    }

    cycle_color();

    return true;
  }

  return false;
}

/**
 * Check if the buttons for setting the time were pressed.
 *
 * @return true if there was a change of time, otherwise false
 */
bool check_time_change() {

  int btn1, btn2, btn3;
  poll_buttons(&btn1, &btn2, &btn3);

  bool result = false;

  /* Button for changing the hour */
  if (btn1 == HIGH) {

    /* wait for release of button */
    while (btn1 == HIGH) {
      poll_buttons(&btn1, &btn2, &btn3);
    }

    /* get actual time */
    int hour;
    int minute;
    int second;
    read_current_time(&hour, &minute, &second);

    /* increase hour and set minutes to zero to avoid
       confusing text on the screen. */
    hour++;
    minute = 0;

    /* warp-around of the hour */
    if (hour > MAX_HOUR) {
      hour = 0;
    }

    trace("Setting hour="); tracenl(hour);

    set_rtc_time(hour, minute, second);
    result = true;
  }

  /* button for changing the minute */
  if (btn2 == HIGH) {

    /* wait for release of button */
    while (btn2 == HIGH) {
      poll_buttons(&btn1, &btn2, &btn3);
    }

    /* get actual time */
    int hour;
    int minute;
    int second;
    read_current_time(&hour, &minute, &second);

    /* round minute down */
    minute = (minute / 5) * 5;

    /* increase minute */
    minute += 5;

    /* warp-around of the minute */
    if (minute > MAX_MINUTE) {
      minute = 0;
    }

    trace("Setting minute="); tracenl(minute);

    set_rtc_time(hour, minute, second);
    result = true;
  }

  return result;
}

/**
 * Poll the state of the buttons on the clock.
 * 1 indicates pressed, 0 indicates not pressed.
 *
 * The function performs a basic debouncing of the button.
 *
 * @param (out) button1 button
 * @param (out) button2 button
 * @param (out) button3 button
*/
void poll_buttons(int *button1, int *button2, int *button3) {

  int btn1a = digitalRead(PORT_BUTTON1);
  int btn2a = digitalRead(PORT_BUTTON2);
  int btn3a = digitalRead(PORT_BUTTON3);

  /* delay and read button state again to perform
     a basic debouncing */
  delay(10);

  int btn1b = digitalRead(PORT_BUTTON1);
  int btn2b = digitalRead(PORT_BUTTON2);
  int btn3b = digitalRead(PORT_BUTTON3);

  *button1 = (btn1a == HIGH) && (btn1b == HIGH);
  *button2 = (btn2a == HIGH) && (btn2b == HIGH);
  *button3 = (btn3a == HIGH) && (btn3b == HIGH);

  trace("poll_buttons: btn1="); trace(*button1);
  trace(", btn2=");             trace(*button2);
  trace(", btn3=");             tracenl(*button3);
}
