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
const int FUENF_M[] = { 7, 8, 9, 10};
const int ZEHN_M[]  = { 11, 12, 13, 14, 15, -1 };
const int ZWANZIG[] = { 15, 16, 17, 18, 19, 20, 21, -1 };
const int DREIVIERTEL[]  = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, -1 };
const int VIERTEL[] = { 26, 27, 28, 29, 30, 31, 32, -1 };
const int VOR[]     = { 35, 36, 37, -1 };
const int NACH[]    = { 38, 39, 40, 41, -1 };
const int HALB[]    = { 44, 45, 46, 47, -1 };
const int ZWOELF[]  = { 49, 50, 51, 52, 53, 54, -1 };
const int ZWEI[]    = { 55, 56, 57, 58, -1 };
const int EINS[]    = { 57, 58, 59, 60, -1 };
const int SIEBEN[]  = { 60, 61, 62, 63, 64, 65, -1 };
const int DREI[]    = { 67, 68, 69, 70, -1 };
const int FUENF[]   = { 71, 72, 73, 74, -1 };
const int ELF[]     = { 77, 78, 79, -1 };
const int NEUN[]    = { 80, 81, 82, 83, -1 };
const int VIER[]    = { 84, 85, 86, 87, -1 };
const int ACHT[]    = { 89, 90, 91, 92, -1 };
const int ZEHN[]    = { 93, 94, 95, 96};
const int SECHS[]   = { 99, 100, 101, 102, 103, -1 };
const int UHR[]     = { 105, 106, 107, -1 };
const int PM[]      = { 109, -1 };
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
static void display_hour(const int hour, int ledBits[]) {
  
  int hourAMPM = hour;
  
  if (hour > 12) {
    compose(PM, ledBits);
    hourAMPM -= 12;
  }

  switch (hourAMPM) {
    
    case 0: compose(ZWOELF, ledBits);
        break;
        
    case 1: compose(EINS, ledBits);
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
  @param (out) ledBits bits for the LEDs
*/
void display_time(const int hour, const int minute, int ledBits[]) {
 
  int roundMinute = (minute / 5) * 5;
  
  compose(ES, ledBits);
  compose(IST, ledBits);
  
  int hourToBeSet = hour;
  
  switch (roundMinute) {
    case 0: compose(UHR, ledBits);
        break;
    
    case 5: compose(FUENF_M, ledBits);
        compose(NACH, ledBits);
        break;
        
    case 10: compose(ZEHN_M, ledBits);
        compose(NACH, ledBits);
        break;

    case 15: compose(VIERTEL, ledBits);
        compose(NACH, ledBits);
        break;

    case 20: compose(ZWANZIG, ledBits);
        compose(NACH, ledBits);
        break;

    case 25: compose(FUENF_M, ledBits);
        compose(VOR, ledBits);
        compose(HALB, ledBits);
        hourToBeSet++;
        break;
        
    case 30: compose(HALB, ledBits);
        hourToBeSet++;
        break;
        
    case 35: compose(FUENF_M, ledBits);
        compose(NACH, ledBits);
        compose(HALB, ledBits);
        hourToBeSet++;
        break;
        
    case 40: compose(ZWANZIG, ledBits);
        compose(VOR, ledBits);
        hourToBeSet++;
        break;
        
    case 45: compose(VIERTEL, ledBits);
        compose(VOR, ledBits);
        hourToBeSet++;
        break;
        
    case 50: compose(ZEHN_M, ledBits);
        compose(VOR, ledBits);
        hourToBeSet++;
        break;
        
    case 55: compose(FUENF_M, ledBits);
        compose(VOR, ledBits);
        hourToBeSet++;
        break;
  }
  
  display_hour(hourToBeSet, ledBits);
}

