/**
  Functions for rendering fonts on the LED display.
*/

#include "fontdef.h"


/**
  Extracts the font definition for a given character from the font array.
  
  @param (out) data the bytes of the character
  @param (in) c the character to extract font information for
  @param (in) font the font definition
  @param (in) height the height of one character in the font in pixel 
*/
void character_definition(byte data[], const char c, const int font[], const int height) {
  
  int offset = 0;
  
  if (c >= '0' && c <= '9') {
    offset = c - '0';
  }
  else if (c >= 'A' && c <= 'Z') {
    offset = c - 'A' + 10;
  }
  else if (c == '?') {
    offset = 36;
  }
  else if (c == ':') {
    offset = 37;
  }
  else {
    offset = 38;
  }
  
  for (int i = 0; i < height; i++) {
    data[i] = font[(offset * height) + i];
  }
}


/**
  Add a charcter from the 5x5 font to the led array at the given position.
  
  Positions outside of the LED array will be silently ignored.
  
  @param (out) ledBits bits for the LEDs (will NOT be cleared)
  @param (in) xpos horizontal position of the characters left upper edge 
              (starts at 0)
  @param (in) ypos vertical position of the characters left upper edge 
              (starts at 0)
  @param (in) c the character to display
*/  
void print_char_5x5(int ledBits[], const int xpos, const int ypos, const char c) {
  print_char(ledBits, xpos, ypos, c, CHAR_SET_5x5, 5, 5);
}

/**
  Add a charcter from the 8x8 font to the led array at the given position.
  
  Positions outside of the LED array will be silently ignored.
  
  @param (out) ledBits bits for the LEDs (will NOT be cleared)
  @param (in) xpos horizontal position of the characters left upper edge 
              (starts at 0)
  @param (in) ypos vertical position of the characters left upper edge 
              (starts at 0)
  @param (in) c the character to display
*/  
void print_char_8x8(int ledBits[], const int xpos, const int ypos, const char c) {
  print_char(ledBits, xpos, ypos, c, CHAR_SET_8x8, 8, 8);
}

/**
  Add a charcter from to the led array at the given position.
  
  Positions outside of the LED array will be silently ignored.
  
  @param (out) ledBits bits for the LEDs (will NOT be cleared)
  @param (in) xpos horizontal position of the characters left upper edge 
              (starts at 0)
  @param (in) ypos vertical position of the characters left upper edge 
              (starts at 0)
  @param (in) c the character to display
  @param (in) font font definition
  @param (in) width width of the font in pixel
  @param (in) height height of the font in pixel
*/  

void print_char(int ledBits[], const int xpos, const int ypos, const char c, 
    const int font[], const int width, const int height) {

  byte data[height];  
  character_definition(data, c, font, height); 
    
  int x = 0;
  int y = 0;
  
  for (int i = 0; i < height; i++) {
    
    for (int k = 0; k < width; k++) {
    
      if ((data[i] & (1 << k)) != 0) {
        
        int effectiveX = xpos + x;
        int effectiveY = ypos + y;
        
        if ((effectiveX < 11) && (effectiveY < 10) && (effectiveX >= 0) && (effectiveY >= 0)) { 
          int ledIndex = (effectiveY) * 11 + (effectiveX);
          ledBits[ledIndex] = 1;
          tracenl(ledIndex);
        }
      }
    
      x++;
    
      if (x >= width) {
        x = 0;
        y++;
      }
    }
  }
}

/**
  Scroll a text on the screen.
  
  @param (in) text the text to be scrolled
  @param (in) delayInMilli delay for the scrolling in milliseconds
*/
void scroll_text_8x8(const char* text, int delayInMilli) {
  char* pos;
  int ledBits[NUMBER_OF_LEDS];
 
  int length = 0;
  pos = (char*) text;
  while (*pos++) length++;
  
  for (int xpos = LED_COLUMNS; xpos > length * -9; xpos--) {
    memfill(ledBits, NUMBER_OF_LEDS, 0);
    
    int offset = 0;
    pos = (char*) text;
    while (*pos) {
      print_char_8x8(ledBits, xpos + (8 * offset++), 1, *pos++);
    }
    
    send_to_shift_registers(ledBits);
  }
}

