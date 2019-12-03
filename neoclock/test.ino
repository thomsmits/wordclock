/**
 * Test the clock display by showing different texts.
 */
#include <string.h>
#include "words.h"

/**
 * Helper function to send a single word to the clock display.
 *
 * @param word the word to show
 */
static void display_word(const uint8_t word[]) {
  uint8_t ledBits[NUMBER_OF_LEDS];
  memset(ledBits, 0, NUMBER_OF_LEDS);
  compose(word, ledBits);
  send_to_leds(ledBits);
  delay(500);
  clear();
}

/**
 * Display all possible words on the clock.
 */
void show_all_words() {
  display_word(ES);
  display_word(IST);
  display_word(FUENF_M);
  display_word(ZEHN_M);
  display_word(ZWANZIG);
  display_word(VIERTEL);
  display_word(DREIVIERTEL);
  display_word(NACH);
  display_word(VOR);
  display_word(HALB);
  display_word(EIN);
  display_word(EINS);
  display_word(ZWEI);
  display_word(DREI);
  display_word(VIER);
  display_word(FUENF);
  display_word(SECHS);
  display_word(SIEBEN);
  display_word(ACHT);
  display_word(NEUN);
  display_word(ZEHN);
  display_word(ELF);
  display_word(UHR);
  display_word(ZWOELF);
}

/**
 * Cycle through all times and colors and display them.
 */
void show_all_times_and_colors() {

  int hour = 0;
  int minute = 0;
  int second = 0;
  int palette_index = 0;

  for (hour = 0; hour <= 24; hour++) {
    for (minute = 0; minute < 60; minute++) {
      delay(500);
      set_rtc_time(hour, minute, second);
      show_current_time();

      cycle_color();
    }
  }
}
