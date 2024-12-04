#include <WS2812FX.h>

#define LED_COUNT 55
#define LED_PIN 5

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const uint8_t gModeCount = 57;
const int gModes[gModeCount] = {
   FX_MODE_STATIC                  ,
   FX_MODE_BLINK                   ,
 FX_MODE_BREATH                  ,
   FX_MODE_COLOR_WIPE              ,
   FX_MODE_COLOR_WIPE_INV          ,
   FX_MODE_COLOR_WIPE_REV          ,
   FX_MODE_COLOR_WIPE_REV_INV      ,
   FX_MODE_COLOR_WIPE_RANDOM       ,
 FX_MODE_RANDOM_COLOR            ,
 FX_MODE_SINGLE_DYNAMIC          ,
 FX_MODE_MULTI_DYNAMIC           ,
 FX_MODE_RAINBOW                 ,
 FX_MODE_RAINBOW_CYCLE           ,
   FX_MODE_SCAN                    ,
   FX_MODE_DUAL_SCAN               ,
   FX_MODE_FADE                    ,
 FX_MODE_THEATER_CHASE           ,
 FX_MODE_THEATER_CHASE_RAINBOW   ,
 FX_MODE_RUNNING_LIGHTS          ,
   FX_MODE_TWINKLE                 ,
   FX_MODE_TWINKLE_RANDOM          ,
 FX_MODE_TWINKLE_FADE            ,
 FX_MODE_TWINKLE_FADE_RANDOM     ,
 FX_MODE_SPARKLE                 ,
   FX_MODE_FLASH_SPARKLE           ,
   FX_MODE_HYPER_SPARKLE           ,
   FX_MODE_STROBE                  ,
   FX_MODE_STROBE_RAINBOW          ,
   FX_MODE_MULTI_STROBE            ,
   FX_MODE_BLINK_RAINBOW           ,
   FX_MODE_CHASE_WHITE             ,
 FX_MODE_CHASE_COLOR             ,
 FX_MODE_CHASE_RANDOM            ,
 FX_MODE_CHASE_RAINBOW           ,
  FX_MODE_CHASE_FLASH             ,
   FX_MODE_CHASE_FLASH_RANDOM      ,
   FX_MODE_CHASE_RAINBOW_WHITE     ,
 FX_MODE_CHASE_BLACKOUT          ,
 FX_MODE_CHASE_BLACKOUT_RAINBOW  ,
   FX_MODE_COLOR_SWEEP_RANDOM      ,
 FX_MODE_RUNNING_COLOR           ,
   FX_MODE_RUNNING_RED_BLUE        ,
 FX_MODE_RUNNING_RANDOM          ,
 FX_MODE_LARSON_SCANNER          ,
   FX_MODE_COMET                   ,
   FX_MODE_FIREWORKS               ,
   FX_MODE_FIREWORKS_RANDOM        ,
 FX_MODE_MERRY_CHRISTMAS         ,
   FX_MODE_FIRE_FLICKER            ,
 FX_MODE_FIRE_FLICKER_SOFT       ,
   FX_MODE_FIRE_FLICKER_INTENSE    ,
 FX_MODE_CIRCUS_COMBUSTUS        ,
 FX_MODE_HALLOWEEN               ,
 FX_MODE_BICOLOR_CHASE           ,
 FX_MODE_TRICOLOR_CHASE          ,
 FX_MODE_TWINKLEFOX,
 FX_MODE_RAIN

};

const char* gModeNames[gModeCount] {
"   FX_MODE_STATIC              "    ,
"   FX_MODE_BLINK               "    ,
" FX_MODE_BREATH                "  ,
"   FX_MODE_COLOR_WIPE          "    ,
"   FX_MODE_COLOR_WIPE_INV      "    ,
"   FX_MODE_COLOR_WIPE_REV      "    ,
"   FX_MODE_COLOR_WIPE_REV_INV  "    ,
"   FX_MODE_COLOR_WIPE_RANDOM   "    ,
" FX_MODE_RANDOM_COLOR          "  ,
" FX_MODE_SINGLE_DYNAMIC        "  ,
" FX_MODE_MULTI_DYNAMIC         "  ,
" FX_MODE_RAINBOW               "  ,
" FX_MODE_RAINBOW_CYCLE         "  ,
"   FX_MODE_SCAN                "    ,
"   FX_MODE_DUAL_SCAN           "    ,
"   FX_MODE_FADE                "    ,
" FX_MODE_THEATER_CHASE         "  ,
" FX_MODE_THEATER_CHASE_RAINBOW "  ,
" FX_MODE_RUNNING_LIGHTS        "  ,
"   FX_MODE_TWINKLE             "    ,
"   FX_MODE_TWINKLE_RANDOM      "    ,
" FX_MODE_TWINKLE_FADE          "  ,
" FX_MODE_TWINKLE_FADE_RANDOM   "  ,
" FX_MODE_SPARKLE               "  ,
"   FX_MODE_FLASH_SPARKLE       "    ,
"   FX_MODE_HYPER_SPARKLE       "    ,
"   FX_MODE_STROBE              "    ,
"   FX_MODE_STROBE_RAINBOW      "    ,
"   FX_MODE_MULTI_STROBE        "    ,
"   FX_MODE_BLINK_RAINBOW       "    ,
"   FX_MODE_CHASE_WHITE         "    ,
" FX_MODE_CHASE_COLOR           "  ,
" FX_MODE_CHASE_RANDOM          "  ,
" FX_MODE_CHASE_RAINBOW         "  ,
"  FX_MODE_CHASE_FLASH          "   ,
"   FX_MODE_CHASE_FLASH_RANDOM  "    ,
"   FX_MODE_CHASE_RAINBOW_WHITE "    ,
" FX_MODE_CHASE_BLACKOUT        "  ,
" FX_MODE_CHASE_BLACKOUT_RAINBOW"  ,
"   FX_MODE_COLOR_SWEEP_RANDOM  "    ,
" FX_MODE_RUNNING_COLOR         "  ,
"   FX_MODE_RUNNING_RED_BLUE    "    ,
" FX_MODE_RUNNING_RANDOM        "  ,
" FX_MODE_LARSON_SCANNER        "  ,
"   FX_MODE_COMET               "    ,
"   FX_MODE_FIREWORKS           "    ,
"   FX_MODE_FIREWORKS_RANDOM    "    ,
" FX_MODE_MERRY_CHRISTMAS       "  ,
"   FX_MODE_FIRE_FLICKER        "    ,
" FX_MODE_FIRE_FLICKER_SOFT     "  ,
"   FX_MODE_FIRE_FLICKER_INTENSE"    ,
" FX_MODE_CIRCUS_COMBUSTUS      "  ,
" FX_MODE_HALLOWEEN             "  ,
" FX_MODE_BICOLOR_CHASE         "  ,
" FX_MODE_TRICOLOR_CHASE        "  ,
" FX_MODE_TWINKLEFOX                   " ,
"FX_MODE_RAIN" 
};

uint8_t currentModeIndex = 0;

void setup() {
  ws2812fx.init();
  ws2812fx.setBrightness(100);
  ws2812fx.setSpeed(200);
  ws2812fx.setMode(gModes[currentModeIndex]);
  ws2812fx.start();
}

void loop() {
  ws2812fx.service();

  // Change the effect every 5 seconds
  const unsigned long interval = 10000; // 5 seconds in milliseconds
  static unsigned long lastChangeTime = 0;

  if (millis() - lastChangeTime >= interval) {
    lastChangeTime = millis();

    // Increment the mode index, wrapping around to 0 if necessary
    currentModeIndex = (currentModeIndex + 1) % gModeCount;

    // Set the new mode and print its name
    ws2812fx.setMode(gModes[currentModeIndex]);
    Serial.print("Current mode: ");
    Serial.println((gModeNames[currentModeIndex]));
  }
}