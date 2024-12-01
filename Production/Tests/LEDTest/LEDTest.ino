#include "LEDController.h"

#define DEBUG 1

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTDEC(x) Serial.print(x, DEC)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#endif

#define LED_COUNT_SCHWERT 110
#define LED_COUNT_KAMM 100
#define LED_COUNT_MAIN 70

#define LED_SCHWERT 7
#define LED_KAMM 8
#define LED_MAIN 9
#define LEDANIMBRIGHTNESS 200
#define LEDANIMSPEED 200
#define LEDANIMDURATION 5000

unsigned long previousMillis = 0;  // Stores the last time the mode was updated
const long interval = 15000;       // Interval to change mode (15 seconds)

// LEDController Instanzen
//                                ledCount,   ledPin, animMode, brightness, speed, animRunDuration);
LEDController ledControllerSchwert(LED_COUNT_SCHWERT, LED_SCHWERT, FX_MODE_RAINBOW_CYCLE,   LEDANIMBRIGHTNESS,        LEDANIMSPEED,   LEDANIMDURATION);
LEDController ledControllerKamm(LED_COUNT_KAMM, LED_KAMM, FX_MODE_RUNNING_LIGHTS,   LEDANIMBRIGHTNESS,        LEDANIMSPEED,   LEDANIMDURATION);
LEDController ledControllerMain(LED_COUNT_MAIN, LED_MAIN, FX_MODE_RUNNING_COLOR,   LEDANIMBRIGHTNESS,        LEDANIMSPEED,   LEDANIMDURATION);

void setup() {

    #ifdef DEBUG
        Serial.begin(9600);
    #endif
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

        // Zufälligen Effekt für Schwert, Kamm und Main auswählen
        int schwertEffect = ledControllerSchwert.getBalrogHitEffect();  // Beispiel für BalrogHit-Effekt
        int kammEffect = ledControllerKamm.getBalrogOpenRampsEffect(); // Beispiel für BalrogOpenRamps-Effekt
        int mainEffect = ledControllerMain.getBalrogClosedRampsEffect(); // Beispiel für BalrogClosedRamps-Effekt

        // Setze die Effekte für die jeweiligen Controller
        //stops the old animation if still running and starts the new one with the according timer
        ledControllerSchwert.setMode(schwertEffect);
        ledControllerKamm.setMode(kammEffect);
        ledControllerMain.setMode(mainEffect);

        // Ausgabe der aktuellen Effekte
        DEBUG_PRINT("Kamm Effekt: ");
        DEBUG_PRINTLN(ledControllerKamm.getEffectName(kammEffect));
        DEBUG_PRINT("Schwert Effekt: ");
        DEBUG_PRINTLN(ledControllerSchwert.getEffectName(schwertEffect));
        DEBUG_PRINT("Main Effekt: ");
        DEBUG_PRINTLN(ledControllerMain.getEffectName(mainEffect));
        DEBUG_PRINTLN("_____________________________________________________");        

     
    }

    // Dienste zur kontinuierlichen Verarbeitung der Animationen
    ledControllerSchwert.service();
    ledControllerKamm.service();
    ledControllerMain.service();
}
