/*
 Displaying information on the LED panel.
*/

/**
  Positions of the text on the LED panel.
  
  As the Arduino programming language cannot determine
  the length of an array that is passed to a function
  as a pointer, a -1 at the end of the array indicates the
  end of the array.
  
  The values of the array have to be <= NUMBER_OF_LEDS - 1.
*/
const int ES[]      = { 0, 1, -1 };
const int IST[]     = { 3, 4, 5, -1 };
const int FUENF_M[] = { 7, 8, 9, 10, -1 };
const int ZEHN_M[]  = { 11, 12, 13, 14, -1 };
const int ZWANZIG[] = { 15, 16, 17, 18, 19, 20, 21, -1 };
const int DREIVIERTEL[]  = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, -1 };
const int VIERTEL[] = { 26, 27, 28, 29, 30, 31, 32, -1 };
const int VOR[]     = { 33, 34, 35, -1 };
const int FUNK[]    = { 36, 37, 38, 39, -1 };
const int NACH[]    = { 40, 41, 42, 43, -1 };
const int HALB[]    = { 44, 45, 46, 47, -1 };
const int ELF[]     = { 49, 50, 51, -1 };
const int FUENF[]   = { 51, 52, 53, 54, -1 };
const int EIN[]     = { 55, 56, 57, -1 };
const int EINS[]    = { 55, 56, 57, 58, -1 };
const int ZWEI[]    = { 62, 63, 64, 65, -1 };
const int DREI[]    = { 66, 67, 68, 69, -1 };
const int VIER[]    = { 73, 74, 75, 76, -1 };
const int SECHS[]   = { 77, 78, 79, 80, 81, -1 };
const int ACHT[]    = { 84, 85, 86, 87, -1 };
const int SIEBEN[]  = { 88, 89, 90, 91, 92, 93, -1 };
const int ZWOELF[]  = { 94, 95, 96, 97, 98, -1 };
const int ZEHN[]    = { 99, 100, 101, 102, -1 };
const int UHR[]     = { 107, 108, 109, -1 };
const int NEUN[]    = { 102, 103, 104, 105, -1 };
const int PM[]      = { 111, -1 };
const int WECKER[]  = { 110, -1 };


/** 
 Sets the bits in resultArray depending on the values of the 
 arrayToAdd. Bits already set in the input array will not
 be set to zero.
 
 WARNING: this function does not perform any bounds checks!
 
 @param arrayToAdd Array containing the bits to be set as 
        index of the bit. The value 5 for example implies
        that the 6th bit in the resultArray has to be set to 1.
        This array has to be terminated by -1.
 
 @param (out) ledBits Array where the bits will be set according
        to the input array. The ledBits has to be big enough to
        accomodate the indices provided in arrayToAdd.
*/        
static void compose(const int arrayToAdd[], int ledBits[]) {
  int pos;
  int i = 0;
    
  while ((pos = arrayToAdd[i++]) != -1) {
    ledBits[pos] = 1;
  }
}

/**
 Sets the hour information for the clock.
 
 @param hour the hour to be set
 @param (out) ledBits array to set led bits
*/
static void display_hour(const int displayHour, const int minute, const int hour, int ledBits[]) {
  
  int hourAMPM = displayHour;
  
  if (hour >= 12) {
    compose(PM, ledBits);
  }
  
  if (displayHour >= 12) {
    hourAMPM -= 12;
  }

  trace("display_hour: ");
  trace("hour=");
  trace(hour);
  trace(", hourAMPM=");
  tracenl(hourAMPM);
  
  
  switch (hourAMPM) {
    
    case 0: compose(ZWOELF, ledBits);
        break;
        
    case 1: 
        if (minute == 0) {
          compose(EIN, ledBits);
        }
        else {
          compose(EINS, ledBits);
        }
        break;

    case 2: compose(ZWEI, ledBits);
        break;
        
    case 3: compose(DREI, ledBits);
        break;
        
    case 4: compose(VIER, ledBits);
        break;
        
    case 5: compose(FUENF, ledBits);
        break;
        
    case 6: compose(SECHS, ledBits);
        break;
        
    case 7: compose(SIEBEN, ledBits);
        break;
        
    case 8: compose(ACHT, ledBits);
        break;
        
    case 9: compose(NEUN, ledBits);
        break;
        
    case 10: compose(ZEHN, ledBits);
        break;
        
    case 11: compose(ELF, ledBits);
        break;
        
    case 12: compose(ZWOELF, ledBits);
        break;
  }  
}

/**
  Displays hour and minutes on the LED panel.
  
  @param hour the hour to be set
  @param minute the minute to be set
  @param (out) ledBits bits for the LEDs (will NOT be cleared)
*/
void display_time(const int hour, const int minute, int ledBits[]) {
 
  int roundMinute = (minute / 5) * 5;

  trace("display_time: ");
  trace("roundMinute=");
  trace(roundMinute);
  
  int displayHour = hour;
  
  switch (roundMinute) {
    case 0: compose(UHR, ledBits);
        tracenl(", case 0");
        break;
    
    case 5: compose(FUENF_M, ledBits);
        compose(NACH, ledBits);
        tracenl(", case 5");
        break;
        
    case 10: compose(ZEHN_M, ledBits);
        compose(NACH, ledBits);
        tracenl(", case 10");
        break;

#ifdef SOUTH_GERMAN_VERSION
    case 15: compose(VIERTEL, ledBits);
        displayHour++;
        tracenl(", case 15-sg");
        break;
#else
    case 15: compose(VIERTEL, ledBits);
        compose(NACH, ledBits);
        tracenl(", case 15-!nsg");
        break;
#endif

    case 20: compose(ZWANZIG, ledBits);
        compose(NACH, ledBits);
        tracenl(", case 20");
        break;

    case 25: compose(FUENF_M, ledBits);
        compose(VOR, ledBits);
        compose(HALB, ledBits);
        displayHour++;
        tracenl(", case 25");
        break;
        
    case 30: compose(HALB, ledBits);
        displayHour++;
        tracenl(", case 30");
        break;
        
    case 35: compose(FUENF_M, ledBits);
        compose(NACH, ledBits);
        compose(HALB, ledBits);
        displayHour++;
        tracenl(", case 35");
        break;
        
    case 40: compose(ZWANZIG, ledBits);
        compose(VOR, ledBits);
        displayHour++;
        tracenl(", case 40");
        break;
        
#ifdef SOUTH_GERMAN_VERSION        
    case 45: compose(DREIVIERTEL, ledBits);
        displayHour++;
        tracenl(", case 45-sg");
        break;
#else
    case 45: compose(VIERTEL, ledBits);
        compose(VOR, ledBits);
        displayHour++;
        tracenl(", case 45-!sg");
        break;
#endif

    case 50: compose(ZEHN_M, ledBits);
        compose(VOR, ledBits);
        displayHour++;
        tracenl(", case 50");
        break;
        
    case 55: compose(FUENF_M, ledBits);
        compose(VOR, ledBits);
        displayHour++;
        tracenl(", case 55");
        break;
    
    default:
        tracenl(", default-case");
  }
  
  display_hour(displayHour, roundMinute, hour, ledBits);
  
  send_to_shift_registers(ledBits);
}

/**
  Sets the alarm clock icon in the LED array.
*/
void turn_alarm_icon_on(int ledBits[]) {
  compose(WECKER, ledBits);
}

/**
  Show the current time on the display of the clock.
*/
void show_current_time() {
 
  int hour;
  int minute;
  int second;

  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
    
  read_current_time(&hour, &minute, &second);
  
  compose(ES, ledBits);
  compose(IST, ledBits);
    
  if (is_alarm_on()) {
    compose(WECKER, ledBits);
  }
  
  display_time(hour, minute, ledBits);
  
  dbg_output_time(hour, minute, second);
}

/**
  Manually set the clocks time by using the buttons of the
  clock.
*/
void set_time_by_button() {
  int btn1, btn2, btn3, btn4;
  int hour, minute, second;
  
  read_current_time(&hour, &minute, &second);

  set_brightness(255);
  show_current_time();
  
  poll_buttons(&btn1, &btn2, &btn3, &btn4);

  while (btn1 == 0) {
    
    poll_buttons(&btn1, &btn2, &btn3, &btn4);
    
    if (btn2 == 1) {
      hour++;
      set_dcf_time(hour, minute, second);
      show_current_time();
      delay(500);
    }
    
    if (btn3 == 1) {
      minute += 5;
      set_dcf_time(hour, minute, second);
      show_current_time();
      delay(500);
    }
  }
}

/**
  Adjust the brightness of the display depending on the
  ambient light.
*/
void adjust_brightness() { 
    int brightness = get_ambient_brightness();
    int ledBrightness = max(255 - brightness, 1);
    set_brightness(ledBrightness);
}

