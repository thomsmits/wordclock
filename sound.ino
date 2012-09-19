/*
  Playing sounds on the arduino.
*/

#define C     1911
#define C1    1804
#define D     1703
#define Eb    1607
#define E     1517
#define F0    1432
#define F1    1352
#define G     1276
#define Ab    1204
#define A     1136
#define Bb    1073
#define B     1012
#define c      955
#define c1     902
#define d      851
#define eb     803
#define e      758
#define f      716
#define f1     676
#define g      638
#define ab     602
#define a      568
#define bb     536
#define b      506
#define R     0

/* Demo melody from the arduino website */
const int DEMO_MELODY[] = {  C,  B,  g,  C,  b,  e,  R,  C,  c,  g, a, C, -1 };
const int DEMO_BEATS[]  = { 16, 16, 16,  8,  8, 16, 32, 16, 16, 16, 8, 8, -1 }; 

/* Super mario brothers melody */
const int SMB_MELODY[] = { e,  e,  e,  c,  e,  g,  G,  c,  G,  E,  A,  B, Bb,  A, G, e, g,  a, f,  g,  e, c, d, B,  c, -1 };
const int SMB_BEATS[]  = { 6, 12, 12,  6, 12, 24, 24, 18, 18, 18, 12, 12,  6, 12, 8, 8, 8, 12, 6, 12, 12, 6, 6, 6, 12, -1 };

/* Double beep, to be repeated */
const int BEEP_MELODY[] = { C,   E, -1 };
const int BEEP_BEATS[]  = { 32, 32, -1 };

/* Overall tempo for sound output */
const long tempo = 10000;

/* Pause between two notes */
const int pause = 1000;

/* Correction factor for pause time that takes into account
   that hardware output routines need some time for execution
   which has to be added to the duration of the note. */
const int rest_count = 100; 

/** User has cancelled sound playing */
boolean stop_sound = false;

/** 
  Beep 
*/
void beep() {
  play_melody(BEEP_MELODY, BEEP_BEATS);
}

/**
  Play a single tone.
  
  @param toneToPlay tone to be played
  @param duration duration of the tone
*/
void play_tone(const int toneToPlay, const long duration) {
  
  long elapsed_time = 0;
  
  if (toneToPlay > 0) { 
    
    while (elapsed_time < duration) {
 
      // UP
      digitalWrite(PORT_SPEAKER, HIGH);
      delayMicroseconds(toneToPlay / 2);

      // DOWN
      digitalWrite(PORT_SPEAKER, LOW);
      delayMicroseconds(toneToPlay / 2);

      // Keep track of how long we pulsed
      elapsed_time += (toneToPlay);
    } 
  }
  else {
    // handle the note R (which is rest)
    for (int j = 0; j < rest_count; j++) { 
      delayMicroseconds(duration);  
    }                                
  }                                 
}


/**
  Loop a melody.
  
  @param melody the notes of the melody
  @param beats the duration of the notes
  @param repeat number of repetitions of the melody
  @param pause between two loops
*/
void loop_melody(const int melody[], const int beats[], const int repeat, const long pause) {
  for (int i = 0; i < repeat; i++) {
    play_melody(melody, beats);
    update();
    if (stop_sound) {
      break;
    }
    
    delay(pause);
  }
  
  stop_sound = false;
}


/**
  Play a melody.
  
  @param melody the notes of the melody
  @param beats the duration of the notes
*/
void play_melody(const int melody[], const int beats[]) {
   
  for (int i = 0; melody[i] > 0; i++) {
    int toneToPlay = melody[i];
    int beat = beats[i];

    long duration = beat * tempo;

    play_tone(toneToPlay, duration); 

    update();
    if (stop_sound) {
      break;
    }
    
    delayMicroseconds(pause);
  }
  
  stop_sound = false;
}
