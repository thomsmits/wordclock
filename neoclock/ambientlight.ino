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
#define FULL_AMBIENT_LIGHT 3000.0

// Measurement of the photo resistor for complete
// darkness
#define NO_AMBIENT_LIGHT 0.0

/**
 * Return the measured value of the ambient light
 * sensor. If no sensor is present (PIN_LIGHTSENSOR no set)
 * the function returns 1.0.
 *
 * @return the measured value in the range of 0.0 and 1.0.
 */
double get_ambient_brightness() {
  int value;
  #ifdef PIN_LIGHTSENSOR
    value = analogRead(PIN_LIGHTSENSOR);
  #else
    return 1.0;
  #endif

  trace("get_ambient_brightness: value=");
  trace(value);

  double scaledValue;

  if (NO_AMBIENT_LIGHT < FULL_AMBIENT_LIGHT) {
    scaledValue = (double) ( (double)value -  NO_AMBIENT_LIGHT) /  FULL_AMBIENT_LIGHT;
  } else {
    scaledValue = (double) ( (double)value -  FULL_AMBIENT_LIGHT) /  NO_AMBIENT_LIGHT;
  }

  trace(", scaledValue=");
  tracenl(scaledValue);

  // ensure that the value does never exceed 255 even if the
  // analog in port delivers a value greater than NO_AMBIENT_LIGHT
  if (scaledValue > 1) {
    scaledValue = 1;
  }

  return scaledValue;
}
