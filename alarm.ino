/*
  Functions to manage alarm setting and
  alarm sounds.
*/

/** Steps for setting the alarm minutes */
#define ALARM_STEPS 5

/** Hour for the alarm */
static int alarm_hour;

/** Minute for the alarm */
static int alarm_minute;

/** Indicates whether the alarm is on or off. */
static boolean alarm_on = false;

/* User has stopped alarm */
boolean stop_alarm = false;

/** 
  Indicates whether the alarm is on or off.
  
  @return true if alarm is on
*/
boolean is_alarm_on() {
  return alarm_on;
}

/**
  Toggels the alarm on/off switch.
*/
void alarm_toggel() {
  if (alarm_on) {
   alarm_on = false;
  }
  else {
    alarm_on = true;
  }
}

/**
  Indicates whether the alarm should be played.
  
  @return true the alarm sound should not be played
          any longer.
  */
boolean stop_alarm_sound() {
  return stop_alarm;
}

/**
  Check whether the alarm button was pressed.
*/
void check_alarm_toggle() {
  int btn1, btn2, btn3, btn4;
  poll_buttons(&btn1, &btn2, &btn3, &btn4);

  if ((btn1 == 0) && (btn4 == 1)) {
    
    // wait until button is released again
    while (btn4 == 1) {
      poll_buttons(&btn1, &btn2, &btn3, &btn4);
    }
    
    if (alarm_on) {
      tracenl("check_alarm_toggle: alarm turned off");
      alarm_on = false;
    }
    else {
      alarm_on = true;
      tracenl("check_alarm_toggle: alarm turned on");
    }
    
    show_current_time();
  }
}

/**
  Check whether the user wants to set the alarm.
*/
void check_alarm_set() {
  int btn1, btn2, btn3, btn4;
  poll_buttons(&btn1, &btn2, &btn3, &btn4);

  if ((btn1 == 1) && (btn4 == 1)) {
    
    // wait until buttons are released again
    while ((btn1 == 1) || (btn4 == 1)) {
      poll_buttons(&btn1, &btn2, &btn3, &btn4);
    }
    
    tracenl("check_alarm_set: buttons pressed");
    set_alarm_by_button();
  }
}

/**
  Manually set the clocks time by using the buttons of the
  clock.
*/
void set_alarm_by_button() {
  int btn1, btn2, btn3, btn4;
  int hour, minute, second;
  
  hour = alarm_hour;
  minute = alarm_minute;
  second = 0;

  set_brightness(255);
  int ledBits[NUMBER_OF_LEDS];
  memfill(ledBits, NUMBER_OF_LEDS, 0);
  
  memfill(ledBits, NUMBER_OF_LEDS, 0);
  turn_alarm_icon_on(ledBits); 
  display_time(hour, minute, ledBits);
      
  poll_buttons(&btn1, &btn2, &btn3, &btn4);

  while (btn1 == 0) {
    
    poll_buttons(&btn1, &btn2, &btn3, &btn4);
    
    if (btn2 == 1) {
      hour++;
      time_wrap(&hour, &minute);
      memfill(ledBits, NUMBER_OF_LEDS, 0);
      turn_alarm_icon_on(ledBits);
      display_time(hour, minute, ledBits);
      delay(500);
    }
    
    if (btn3 == 1) {
      minute += ALARM_STEPS;
      time_wrap(&hour, &minute);
      memfill(ledBits, NUMBER_OF_LEDS, 0);
      turn_alarm_icon_on(ledBits);
      display_time(hour, minute, ledBits);
      delay(500);
    }
  }
  
  alarm_hour = hour;
  alarm_minute = minute;
  
  show_current_time();
   
  trace("set_alarm_by_button: alarm set to hour=");
  trace(hour);
  trace(", minute=");
  tracenl(minute);
}

/**
  Check whether it is time to play an alarm.
*/
void check_alarm() {
  
  if (!alarm_on) {
    return;
  }
  
  int hour;
  int minute;
  int second;

  read_current_time(&hour, &minute, &second);

  trace("check_alarm: hour=");
  trace(hour);
  trace(", minute=");
  trace(minute);
  trace(", alarm_hour=");
  trace(alarm_hour);
  trace(", alarm_minute=");
  trace(alarm_minute);  
  
  if ((alarm_hour == hour) && (alarm_minute == minute) && !stop_alarm) {
    trace(", ALARM ACTIVE");
    show_current_time();
    alarm_melody();
  }
  
  // reset the stop alarm function
  if ((alarm_hour == hour) && (alarm_minute + 1 == minute)) {
    stop_alarm = false;
  }
  
  tracenl("");
}

/**
  Indicates whether the user has requested to stop
  playing the alarm by pressing any button.
*/
boolean stop_sound() {
  int btn1, btn2, btn3, btn4;
  poll_buttons(&btn1, &btn2, &btn3, &btn4);
  
  stop_alarm = ((btn1 == 1) || (btn2 == 1) || (btn3 == 1) || (btn4 == 1));  
  
  return stop_alarm;
}

