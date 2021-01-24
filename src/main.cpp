// Arduino for Musicians
// Metronome 2

#include <Arduino.h>

// Constants for output of tone to speaker
const int speakerPin = 9;
const int frequency = 880;
const int duration = 50;
const unsigned int msPerMinute = 60000;

// Potentiometer pin
const int potPin = 0;

// Additional variables
unsigned int MS_per_beat = 0;
unsigned int beats_per_minute = 60;
int potValue;

void setup() {
  // Calculate the amount of delay:
  // milliseconds per minute / beats per minute
  MS_per_beat = msPerMinute / beats_per_minute;
}

void loop() {
  //  Check the status of the potentiometer
  int value = analogRead(potPin);

  // Recalculate tempo if the pot value has changed
  if (value != potValue) {
    // Map the value to a reasonable metronome range between
    // 30 and 350 BPM.
    beats_per_minute = map(value, 0, 1023, 30, 350);

    // Recalculate the delay time and update pot value
    MS_per_beat = msPerMinute / beats_per_minute;
    potValue = value;

  }
  // Output the tone
  tone(speakerPin, frequency, duration);

  // Delay loop for specified amount of time
  delay(MS_per_beat);
}