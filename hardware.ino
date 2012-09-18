/*
  Functions to handle the hardware of the clock.
*/

//#define SCOPE_DELAY 100

// serial signal (PIN 2)
#define PORT_SER_IN 12

// send to output port (IN 8)
#define PORT_OUTPUT_ENABLE 8

// clear buffer (PIN 7)
#define PORT_CLEAR 7

// clock for shift register port (PIN 15)
#define PORT_SRCK 11

// clock for register (PIN 10)
#define PORT_RCK 10

#define PORT_SPEAKER 9
#define PORT_BUTTON1 2

#define PORT_LED 13

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
  pinMode(PORT_BUTTON1, INPUT);
  pinMode(PORT_DCF, INPUT);
  pinMode(PORT_LED, OUTPUT);
}


void write_to_port(int port, int signal) {
  
  digitalWrite(port, signal);
  
  #ifdef SCOPE_DELAY
  delayMicroseconds(SCOPE_DELAY);
  #endif 
}

/**
 Sents the given bit patternto the shift registers
 connected to pin PORT_SIGNAL.
 
 @param ledBits the bit pattern to be sent
*/
void send_to_shift_registers(const int bitPattern[]) {
  
  // ensure PORT_RCK is off to avoid flickering during
  // shift operation
  write_to_port(PORT_RCK, LOW);
  
  // clear all shift registers
  write_to_port(PORT_CLEAR, LOW);
  write_to_port(PORT_CLEAR, HIGH);
  
  // enable transfer of data to next shift register
  // turn of drains
  write_to_port(PORT_OUTPUT_ENABLE, HIGH);
  
  // ensure that clock is low
  write_to_port(PORT_SRCK, LOW);
  
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    
    if (bitPattern[i] == 1) {
      write_to_port(PORT_SER_IN, HIGH);
    }
    else {
      write_to_port(PORT_SER_IN, LOW);
    }
   
    // data is taken from PORT_SER_IN on up flank of
    // PORT_SRCK, therefore trigger PORT_SRCK to transfer bit of
    // PORT_SER_IN to shift register
    write_to_port(PORT_SRCK, HIGH);
    write_to_port(PORT_SRCK, LOW);
  }    
  
  //  trigger PORT_RCK to transfer data from shift registers
  // into the output buffer
  write_to_port(PORT_RCK, HIGH);
  write_to_port(PORT_RCK, LOW);
  
  // turn on drains
  write_to_port(PORT_OUTPUT_ENABLE, LOW);
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


#define FULL_AMBIENT_LIGHT 0
#define NO_AMBIENT_LIGHT 700.0

/**
  Get the ambient brightness (of the room).
  
  @return 255 indicates maximum brightness
  @return 0 indicates complete darkness
*/
int get_ambient_brightness() {
  int value = analogRead(A0);
  
  int scaledValue = (double) (value - FULL_AMBIENT_LIGHT) / NO_AMBIENT_LIGHT * 255.0;
 
  // ensure that the value does never exceed 255 even if the
  // analog in port delivers a value greater than NO_AMBIENT_LIGHT
  if (scaledValue > 255) {
    scaledValue = 255;
  }
  
  return scaledValue;
}
