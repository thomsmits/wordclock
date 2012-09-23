/*
  Functions to handle the hardware of the clock.
*/

// delay for signal tracing with an 
// (slow) oscilloscope. Comment in to activate
//#define SCOPE_DELAY 10000

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

// Measurement of the photo resistor for maximum
// light
#define FULL_AMBIENT_LIGHT 0

// Measurement of the photo resistor for complete
// darkness
#define NO_AMBIENT_LIGHT 1000.0

/**
  Initialize hardware.
*/
void hardware_initialize() {
  pinMode(PORT_SER_IN, OUTPUT);
  pinMode(PORT_OUTPUT_ENABLE, OUTPUT);
  pinMode(PORT_CLEAR, OUTPUT);
  pinMode(PORT_SRCK, OUTPUT);
  pinMode(PORT_RCK, OUTPUT);
  pinMode(PORT_SPEAKER, OUTPUT);
  pinMode(PORT_DCF, INPUT);
  pinMode(PORT_LED, OUTPUT);
 
  // disable output of shift-registers
  // (inverted signal): HIGH => off
  high(PORT_OUTPUT_ENABLE);
}

/**
  Set the given port to potential HIGH.
  
  @param port the port to set
*/
void high(int port) {
  
  digitalWrite(port, HIGH);

  #ifdef SCOPE_DELAY
  delayMicroseconds(SCOPE_DELAY);
  #endif 
  
}

/**
  Set the given port to potential LOW.
  
  @param port the port to set
*/
void low(int port) {
  
  digitalWrite(port, LOW);

  #ifdef SCOPE_DELAY
  delayMicroseconds(SCOPE_DELAY);
  #endif 
  
}

/**
 Sends the given bit pattern to the shift registers
 connected to the arduino. 
 
 The shift register chips have the following schematic
 design:
                                      | OUTPUT_ENABLED
         +----------+   +----------+  |  
 INPUT --|  shift   |---| storage  |--&-- DRAIN
         | register |   | register |  |
         +----------+   +----------+  |
              |                       |
       +------+ OUTPUT                |
       |                              | 
       | +----------+   +----------+  | 
 INPUT +-|  shift   |---| storage  |--&-- DRAIN
         | register |   | register |
         +----------+   +----------+
              |
             ... 
 
 INPUT:  SER_IN, SRCK, RCK, CLEAR
 DRAIN:  LED connection
 OUTPUT: Bit output of the chip connected to SER_IN of 
         the next chip 
 OUTPUT_ENABLED: control whether content of storage regsiter
         is visible on DRAIN or not
 
 The protocoll to talk with the shift registers is as
 follows:
 
 1. Set SER_IN to the desired bit value (HIGH or LOW).
 2. Trigger a clock signal on SRCK (LOW -> HIGH -> LOW).
 3. The bit is stored in the shift register and the last
    bit of the register is shifted to the output port
    
    E.g. The register contains the value 10101101, now a 
    1 is moved into the register with the above protocol.
    After this step, the register contains the value
    11010110 and the output port as the value 1. If now 
    another 1 is moved into the register, it has the value
    11101011 and the output port is 0.
 
 Repeat steps 1. and 2. until all the bits are send to
 the shift register chain.
 
 Now all the desired bits are in the shift registers of the chip
 chain (first stage of the chip).
 
 4. By triggering the RCK clock (LOW -> HIGH -> LOW), the values of
    the first stage are moved into the second stage of the chip.
 
 Whether the data is directly send to the output of the chips
 connected to (DRAIN) or not depends on the signal: OUTPUT_ENABLE.
 If OUTPUT_ENABLE is HIGH, the drains are turned off, if it is
 LOW, the bits from the register part are sent to the DRAIN port.
 
 @param ledBits the bit pattern to be sent. The length of the array 
        has to be as defined in NUMBER_OF_LEDS. No bounds check performed!
*/
void send_to_shift_registers(const int ledBits[]) {

  // stop clearing data by setting inverted clear port
  // to HIGH -> clear is OFF
  high(PORT_CLEAR);
  
  for (int i = NUMBER_OF_LEDS -1; i >= 0; i--) {
    
    // set PORT_SER_IN according  to the data in the array
    if (ledBits[i] == 1) {
      high(PORT_SER_IN);
    }
    else {
      low(PORT_SER_IN);
    }
  
    // trigger clock to move data from SER_IN into the
    // the chip  
    high(PORT_SRCK);
    low(PORT_SRCK);
    
    low(PORT_SER_IN);
  }
  
  // ensure that input port is low (to ease debugging)
  low(PORT_SER_IN);
  
  // trigger register clock to move data into the
  // register part of the chip
  high(PORT_RCK);
  low(PORT_RCK);
  
  // enable output and display result
  //low(PORT_OUTPUT_ENABLE);
}

/**
 Set the brightness of the clock.
 
 @param value brightness where 255 indicates full
        brightness, 1 lowes possible and 0 off.
*/
void set_brightness(const int value) {
  int pwm = 255 - value;
  analogWrite(PORT_OUTPUT_ENABLE, pwm);
}

/**
  Get the ambient brightness (of the room).
  
  @return 255 indicates maximum brightness
  @return 0 indicates complete darkness
*/
int get_ambient_brightness() {
  int value = analogRead(PORT_LIGHT_SENSOR);
  
  trace("get_ambient_brightness: value=");
  trace(value);
  
  int scaledValue = (double) (value - FULL_AMBIENT_LIGHT) / NO_AMBIENT_LIGHT * 255.0;
 
  trace(", scaledValue=");
  tracenl(scaledValue);
  
  // ensure that the value does never exceed 255 even if the
  // analog in port delivers a value greater than NO_AMBIENT_LIGHT
  if (scaledValue > 255) {
    scaledValue = 255;
  }
  
  return scaledValue;
}

/**
 Fill the given array with the given value.
 
 As the Ardunio programming language does not initialize
 arrays on the stack with a value, all arrays dynamically
 created need to be filled with a default value manually.
 Use this function to perform this.
 
 @param array (out) the array to be filled
 @param length the length of the array
 @param value the value to fill array with
*/
void memfill(int array[], const int length, const int value) {
  for (int i = 0; i < length; i++) {
    array[i] = value;
  }
}

/**
  Poll the state of the buttons on the clock. 
  1 indicates pressed, 0 indicates not pressed.
  
  The function performs a basic debouncing of the button.
  
  @param (out) button1 button 
  @param (out) button2 button 
  @param (out) button3 button 
  @param (out) button4 button 
*/
void poll_buttons(int *button1, int *button2, int *button3, int *button4) {

  int btn1a = digitalRead(PORT_BUTTON1);
  int btn2a = digitalRead(PORT_BUTTON2);
  int btn3a = digitalRead(PORT_BUTTON3);
  int btn4a = digitalRead(PORT_BUTTON4);
  
  // delay and read button state again to perform
  // a basic debouncing
  delay(10);
  
  int btn1b = digitalRead(PORT_BUTTON1);
  int btn2b = digitalRead(PORT_BUTTON2);
  int btn3b = digitalRead(PORT_BUTTON3);
  int btn4b = digitalRead(PORT_BUTTON4);
  
  *button1 = (btn1a == 1) && (btn1b == 1);
  *button2 = (btn2a == 1) && (btn2b == 1);
  *button3 = (btn3a == 1) && (btn3b == 1);
  *button4 = (btn4a == 1) && (btn4b == 1);
 /* 
  trace("poll_buttons: btn1=");
  trace(*button1);
  trace(", btn2=");
  trace(*button2);
  trace(", btn3=");
  trace(*button3);
  trace(", btn4=");
  tracenl(*button4);
  */
}


 

