#include "LEDController.h"


#define LED_COUNT_SCHWERT 90
#define LED_COUNT_KAMM 100
#define LED_COUNT_MAIN 70

#define LED_SCHWERT 7
#define LED_KAMM 8
#define LED_MAIN 9

unsigned long previousMillis = 0;  // Stores the last time the mode was updated
const long interval = 15000;       // Interval to change mode (15 seconds)
uint8_t currentMode = FX_MODE_STATIC; // Start with the first mode

// Mode names array
const char* modeNames[] = {
  "STATIC",
  "BLINK",
  "BREATH",
  "COLOR_WIPE",
  "COLOR_WIPE_INV",
  "COLOR_WIPE_REV",
  "COLOR_WIPE_REV_INV",
  "COLOR_WIPE_RANDOM",
  "RANDOM_COLOR",
  "SINGLE_DYNAMIC",
  "MULTI_DYNAMIC",
  "RAINBOW",
  "RAINBOW_CYCLE",
  "SCAN",
  "DUAL_SCAN",
  "FADE",
  "THEATER_CHASE",
  "THEATER_CHASE_RAINBOW",
  "RUNNING_LIGHTS",
  "TWINKLE",
  "TWINKLE_RANDOM",
  "TWINKLE_FADE",
  "TWINKLE_FADE_RANDOM",
  "SPARKLE",
  "FLASH_SPARKLE",
  "HYPER_SPARKLE",
  "STROBE",
  "STROBE_RAINBOW",
  "MULTI_STROBE",
  "BLINK_RAINBOW",
  "CHASE_WHITE",
  "CHASE_COLOR",
  "CHASE_RANDOM",
  "CHASE_RAINBOW",
  "CHASE_FLASH",
  "CHASE_FLASH_RANDOM",
  "CHASE_RAINBOW_WHITE",
  "CHASE_BLACKOUT",
  "CHASE_BLACKOUT_RAINBOW",
  "COLOR_SWEEP_RANDOM",
  "RUNNING_COLOR",
  "RUNNING_RED_BLUE",
  "RUNNING_RANDOM",
  "LARSON_SCANNER",
  "COMET",
  "FIREWORKS",
  "FIREWORKS_RANDOM",
  "MERRY_CHRISTMAS",
  "FIRE_FLICKER",
  "FIRE_FLICKER_SOFT",
  "FIRE_FLICKER_INTENSE",
  "CIRCUS_COMBUSTUS",
  "HALLOWEEN",
  "BICOLOR_CHASE",
  "TRICOLOR_CHASE",
  "TWINKLEFOX",
  "RAIN",
  "CUSTOM_0",
  "CUSTOM_1",
  "CUSTOM_2",
  "CUSTOM_3",
  "CUSTOM_4",
  "CUSTOM_5",
  "CUSTOM_6",
  "CUSTOM_7"
};

                                                                       //brightness, speed, duration in millis 
LEDController ledControllerSchwert(LED_COUNT_SCHWERT, LED_SCHWERT, FX_MODE_RAINBOW_CYCLE,   200,        200,   40000); // Adjust parameters as needed
LEDController ledControllerKamm(LED_COUNT_KAMM, LED_KAMM, FX_MODE_RUNNING_LIGHTS,   200,        200,   40000); // Adjust parameters as needed
LEDController ledControllerMain(LED_COUNT_MAIN, LED_MAIN, FX_MODE_RUNNING_COLOR,   100,        200,   40000); // Adjust parameters as needed
void setup() {
  ledControllerSchwert.init();
  ledControllerSchwert.start();
  ledControllerKamm.init();
  ledControllerKamm.start();
  ledControllerMain.init();
  ledControllerMain.start();
}

void loop() {

    unsigned long currentMillis = millis();  

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Increment the mode, wrapping around when it exceeds the number of modes
    currentMode++;
    if (currentMode > FX_MODE_CUSTOM_7) {
      currentMode = FX_MODE_STATIC;  // Wrap back to the first mode
    }

    // Set the new mode in WS2812FX library
    ledControllerSchwert.setMode(currentMode);
    ledControllerKamm.setMode(currentMode);
    ledControllerMain.setMode(currentMode);

    // Print the current mode name to the serial monitor
    Serial.print("Current Mode: ");
    Serial.println(modeNames[currentMode]);

    ledControllerSchwert.stop();
    ledControllerKamm.stop();
    ledControllerMain.stop();
    // Start the effect on the LED strip
    ledControllerSchwert.start();
    ledControllerKamm.start();
    ledControllerMain.start();        
  }

    
    ledControllerSchwert.service();
    ledControllerKamm.service();
    ledControllerMain.service();
}
