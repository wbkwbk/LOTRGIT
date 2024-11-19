#include "LEDController.h"

#define LED_COUNT 60
#define LED_PIN 7
                                                                       //brightness, speed, duration in millis 
LEDController ledController(LED_COUNT, LED_PIN, FX_MODE_RAINBOW_CYCLE,   100,        200,   5000); // Adjust parameters as needed

void setup() {
  ledController.init();
  ledController.start();
}

void loop() {
    ledController.service();
}
