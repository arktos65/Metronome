// Arduino for Musicians
// Metronome 3

#include <Arduino.h>

// Uno board pin constants
const int speakerPin = 9;
const int potPin = 0;
const int pushButtonPin = 2;

// Constants for output of tone to speaker
const int frequency = 880;
const int duration = 50;
const unsigned int msPerMinute = 60000;

// Additional variables
unsigned int MS_per_beat = 0;
unsigned int beats_per_minute = 60;
int pot_value;
int push_button_status = HIGH;
boolean on = false;
long last_time = 0;

//
// Check the status of the potentiometer
//
void checkPot() {
   //  Read the pot value
  int value = analogRead(potPin);

  // Recalculate tempo if the pot value has changed
  if (value != pot_value) {
    // Map the value to a reasonable metronome range between
    // 30 and 350 BPM.
    beats_per_minute = map(value, 0, 1023, 30, 350);

    // Recalculate the delay time and update pot value
    MS_per_beat = msPerMinute / beats_per_minute;
    pot_value = value;

  }
}

//
// Check the state of the push button
//
void checkPushButton() {
  // Check the digital pin for a button press event
  int button_state = digitalRead(pushButtonPin);

  // Was the button pressed?
  if (button_state == LOW && button_state != push_button_status) {
    // Swap on off states
    on =! on;

    // Update the button status
    push_button_status = button_state;

    // Use a delay for a kludgy form of debouncing
    delay(20);
  }

  // Check for button release
  if (button_state == HIGH && button_state != push_button_status) {
    // Update the push button status to OFF
    push_button_status = button_state;
    delay(20);
  }
}

//
// Initialize the board
//
void setup() {
  // Set the digital pin for input and pullup resisitor
  pinMode(pushButtonPin, INPUT_PULLUP);

  // Calculate the amount of delay
  MS_per_beat = msPerMinute / beats_per_minute;
}

//
// Main execution loop
///
void loop() {
  checkPushButton();
  checkPot();

  // Play tone if metronome is ON
  long current_time = millis();
  if ((current_time - last_time >= MS_per_beat) && on == true) {
    // Output the tone
    tone(speakerPin, frequency, duration);
    last_time = current_time;
  }
}