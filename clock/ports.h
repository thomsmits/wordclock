/*
  Definition of the ports used by the word clock.
*/

#ifndef __ports_h
#define __ports_h

// clock for shift register port (PIN 15)
#define PORT_SRCK 2

// serial signal (PIN 2)
#define PORT_SER_IN 3

// clock for register (PIN 10)
#define PORT_RCK 4

// clear buffer (PIN 7)
#define PORT_CLEAR 5

// send to output port (IN 8)
#define PORT_OUTPUT_ENABLE 6

// piezzo speaker
#define PORT_SPEAKER 11

// on-board LED of Arduino
#define PORT_LED 13

// button number one
#define PORT_BUTTON1 8

// button number two
#define PORT_BUTTON2 9

// button number three
#define PORT_BUTTON3 10

// button number four
#define PORT_BUTTON4 12

// light sensor port
#define PORT_LIGHT_SENSOR A0

// port the DCF clock is connected to
#define PORT_DCF 7

#endif
