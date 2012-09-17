/*
  Functions to handle the hardware of the clock.
*/

#define BIT_ON_DELAY 1 
#define BIT_OFF_DELAY 1


// serial signal (PIN 2)
#define PORT_SER_IN 12

// send to output port
#define PORT_OUTPUT_ENABLE 8

// clear buffer (PIN 7)
#define PORT_CLEAR 7

// clock for shift register port (PIN 15)
#define PORT_SRCK 11

// clock for register (PIN 10)
#define PORT_RCK 10

// enable output (PIN 8)
#define PORT_OUTPUT_ENABLE 8


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


/**
 Sents the given bit patternto the shift registers
 connected to pin PORT_SIGNAL.
 
 @param ledBits the bit pattern to be sent
*/
void send_to_shift_registers(const int bitPattern[]) {

  digitalWrite(PORT_OUTPUT_ENABLE, HIGH);
  digitalWrite(PORT_CLEAR, HIGH);
  digitalWrite(PORT_SRCK, LOW);
  
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    
    digitalWrite(PORT_SRCK, LOW);
    
    if (bitPattern[i] == 1) {
      digitalWrite(PORT_SER_IN, HIGH);
    }
    else {
      digitalWrite(PORT_SER_IN, LOW);
    }
    
    //delayMicroseconds(BIT_ON_DELAY);
    digitalWrite(PORT_SRCK, HIGH);
    //delayMicroseconds(BIT_OFF_DELAY);
  }    
  
  digitalWrite(PORT_RCK, HIGH);
  //delayMicroseconds(BIT_ON_DELAY);
  digitalWrite(PORT_RCK, LOW);
  //delayMicroseconds(BIT_OFF_DELAY);
  
  Serial.print("Output Done");
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
  
  int scaledValue = (double) value / NO_AMBIENT_LIGHT * 255.0;
 
  // ensure that the value does never exceed 255 even if the
  // analog in port delivers a value greater than NO_AMBIENT_LIGHT
  if (scaledValue > 255) {
    scaledValue = 255;
  }
  
  return scaledValue;
}
