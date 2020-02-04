/*
 * Functions to handle ambient light sensor attached to micro controller.
*/

#include <stdint.h>
#include "ports.h"

/*
 *  D2  ------------+
 *                  |
 *  GND ----|10k|---+
 *                  |
 *                #LDR#
 *                  |
 *  3,3V -----------+
 */

// Measurement of the photo resistor for maximum
// light
#define FULL_AMBIENT_LIGHT 3000

// Measurement of the photo resistor for complete
// darkness
#define NO_AMBIENT_LIGHT 0.0

/**
 * Initialize the light sensor
 */
void light_sensor_init() {
}


int light_sensor_read() {
  #ifdef PIN_LIGHTSENSOR
    return get_ambient_brightness();
  #else
    return 255;
  #endif
}

int get_ambient_brightness() {
  int value = analogRead(PIN_LIGHTSENSOR);
  
  trace("get_ambient_brightness: value=");
  trace(value);
  
  int scaledValue;

  if (NO_AMBIENT_LIGHT < FULL_AMBIENT_LIGHT) {
    scaledValue = (double) (value - NO_AMBIENT_LIGHT) / FULL_AMBIENT_LIGHT * 255.0;
  } else {
    scaledValue = (double) (value - FULL_AMBIENT_LIGHT) /  NO_AMBIENT_LIGHT * 255.0;
  }
  
  trace(", scaledValue=");
  tracenl(scaledValue);
  
  // ensure that the value does never exceed 255 even if the
  // analog in port delivers a value greater than NO_AMBIENT_LIGHT
  if (scaledValue > 255) {
    scaledValue = 255;
  }
  
  return scaledValue;
}
