#include "GandalfMagicWand.h"

// Constructor to initialize the LED pin
GandalfMagicWand::GandalfMagicWand(int pin) {
  _ledPin = pin;
  pinMode(_ledPin, OUTPUT);  // Set the LED pin as an output
  _ledState = LOW;           // Initially turn off the LED
  _lastFlashMillis = 0;      // Start the flashing timer at 0
  _flashDuration = 0;        // No flash duration initially
}

// Method to start the lightning effect for a specified duration
void GandalfMagicWand::start(int duration) {
  _duration = duration;
  _startMillis = millis();  // Store the start time
}

// Non-blocking method to update the lightning effect
void GandalfMagicWand::update() {
  // If the effect has been running for the specified duration, stop it
  if (millis() - _startMillis >= _duration) {
    return;
  }

  // Check if it's time to flash the LED
  unsigned long currentMillis = millis();

  // If the flash duration has expired, turn off the LED and calculate the next flash duration
  if (currentMillis - _lastFlashMillis >= _flashDuration || isBalrogOpen) {
    _ledState = !_ledState;  // Toggle LED state
    digitalWrite(_ledPin, _ledState ? HIGH : LOW);  // Set the LED state

    // Set the new random flash duration (between 10ms and 100ms)
    _flashDuration = random(10, 100);

    // Update the last flash time
    _lastFlashMillis = currentMillis;
  }
}

void GandalfMagicWand::setBalrogOpenState(boolean balrogstate) {
    isBalrogOpen = balrogstate;
}
