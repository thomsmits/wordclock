/*
  Functions to manage alarm setting and
  alarm sounds.
*/

#define ALARM_STEPS 5
#define ALARM_STEPS_FAST 30

/** Hour for the alarm */
static int alarm_hour;

/** Minute for the alarm */
static int alarm_minute;

/** Indicates whether the alarm is on or off. */
static boolean alarm_on = false;

/* User has stopped alarm */
boolean stop_alarm = false;

/**
  Increments the alarm time by ALARM_STEPS minutes.
  Wrap-around is handled by this function.
*/
void alarm_time_increment() {
  alarm_minute += ALARM_STEPS;
  time_wrap(&alarm_hour, &alarm_minute);
}


/**
  Increments the alarm time by ALARM_STEPS_FAST minutes.
  Wrap-around is handled by this function.
*/
void alarm_time_increment_fast() {
  alarm_minute += ALARM_STEPS_FAST;
  time_wrap(&alarm_hour, &alarm_minute);
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

