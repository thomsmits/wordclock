/*
  Time management functions.
*/

/**
  Convert hour, minute and second to timestamp.

  @param hour hour
  @param minute minute
  @param second second
  @param (out) timestamp in milliseconds
*/
void time_to_millis(int hour, int minute, int second, unsigned long* timestamp);

/**
  Convert timestamp to hour, minute, second.

  @param timestamp timestamp in milliseconds
  @param (out) hour hour
  @param (out) minute minute
  @param (out) second second
*/
void millis_to_time(unsigned long timestamp, int* hour, int* minute, int* second);

/**
  Manage time wrap around on hour and minute.
  If minute is > 60, hour is incremented.
  If hour is > 24, it is set to hour =- 24.

  @param hour (in, out) hour
  @param minute (int, out) minute
*/
void time_wrap(int* hour, int* minute);
