#include "LEDController.h"

#define LED_COUNT_SCHWERT 105
#define LED_COUNT_KAMM 100
#define LED_COUNT_MAIN 70

#define LED_SCHWERT 7
#define LED_KAMM 8
#define LED_MAIN 9


LEDController ledControllerSchwert(LED_COUNT_SCHWERT, LED_SCHWERT, FX_MODE_RAINBOW_CYCLE, 200, 200, 40000);
LEDController ledControllerKamm(LED_COUNT_KAMM, LED_KAMM, FX_MODE_RUNNING_LIGHTS, 200, 200, 40000);
LEDController ledControllerMain(LED_COUNT_MAIN, LED_MAIN, FX_MODE_RUNNING_COLOR, 200, 200, 40000);

void setup() {
  // Create LEDController instances
  ledControllerSchwert.init();
  ledControllerKamm.init();
  ledControllerMain.init();
  ledControllerSchwert.start();
  ledControllerKamm.start();
  ledControllerMain.start();

}

void loop() {
  ledControllerSchwert.service();  
  ledControllerKamm.service(); 
  ledControllerMain.service(); 
}