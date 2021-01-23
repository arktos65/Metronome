// Arduino for Musicians
// Metronome 1

#include <Arduino.h>

// Constants for output of tone to speaker
const int speakerPin = 9;
const int frequency = 880;
const int duration = 50;

// Additional variables
unsigned int MS_per_beat = 0;

void setup() {
  // Calculate the amount of delay:
  // milliseconds per minute / beats per minute
  unsigned int milliseconds_per_minute = 1000 * 60;
  unsigned int beats_per_minute = 60;
  MS_per_beat = milliseconds_per_minute / beats_per_minute;
}

void loop() {
  // Output the tone
  tone(speakerPin, frequency, duration);

  // Delay loop for specified amount of time
  delay(MS_per_beat);
}