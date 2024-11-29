#include "GandalfMagicWand.h"

int ledPin = 9;  // Pin where the LED is connected

GandalfMagicWand wand(ledPin);  // Create a GandalfMagicWand object

void setup() {
  // Start the lightning effect for 10 seconds
  wand.start(5000);
}

void loop() {
  // Update the magic wand effect every loop cycle
  wand.update();
}
