#include "LEDController.h"

#define LED_COUNT_SCHWERT 90
#define LED_COUNT_KAMM 100
#define LED_COUNT_MAIN 70

#define LED_SCHWERT 7
#define LED_KAMM 8
#define LED_MAIN 9

unsigned long previousMillis = 0;  // Stores the last time the mode was updated
const long interval = 15000;       // Interval to change mode (15 seconds)

// LEDController Instanzen
LEDController ledControllerSchwert(LED_COUNT_SCHWERT, LED_SCHWERT, FX_MODE_RAINBOW_CYCLE,   200,        200,   40000);
LEDController ledControllerKamm(LED_COUNT_KAMM, LED_KAMM, FX_MODE_RUNNING_LIGHTS,   200,        200,   40000);
LEDController ledControllerMain(LED_COUNT_MAIN, LED_MAIN, FX_MODE_RUNNING_COLOR,   100,        200,   40000);

void setup() {
  Serial.begin(9600);
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
        ledControllerSchwert.setMode(schwertEffect);
        ledControllerKamm.setMode(kammEffect);
        ledControllerMain.setMode(mainEffect);

        // Ausgabe der aktuellen Effekte
        Serial.print("Kamm Effekt: ");
        Serial.println(ledControllerKamm.getEffectName(kammEffect));
        Serial.print("Schwert Effekt: ");
        Serial.println(ledControllerSchwert.getEffectName(schwertEffect));
        Serial.print("Main Effekt: ");
        Serial.println(ledControllerMain.getEffectName(mainEffect));
        Serial.println("_____________________________________________________");        

        // Stoppe und starte die Effekte erneut
        ledControllerSchwert.stop();
        ledControllerKamm.stop();
        ledControllerMain.stop();
        
        ledControllerSchwert.start();
        ledControllerKamm.start();
        ledControllerMain.start();        
    }

    // Dienste zur kontinuierlichen Verarbeitung der Animationen
    ledControllerSchwert.service();
    ledControllerKamm.service();
    ledControllerMain.service();
}
