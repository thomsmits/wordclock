/*
 * Functions to handle ambient light sensor attached to micro controller.
*/

#include <stdint.h>
#include "ports.h"

#ifndef __ambientlight_h__
#define __ambientlight_h__

/**
 * Return the measured value of the ambient light
 * sensor. If no sensor is present (PIN_LIGHTSENSOR no set)
 * the function returns 1.0.
 *
 * @return the measured value in the range of 0.0 and 1.0.
 */
double get_ambient_brightness();

#endif
