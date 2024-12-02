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

#define LED_COUNT_GANDALF 55


#define LED_GANDALF 7
#define LEDANIMBRIGHTNESSMAIN 200
#define LEDANIMBRIGHTNESKAMMUNDSCHWERT 200
#define LEDANIMSPEED 200
#define LEDANIMDURATION 5000

unsigned long previousMillis = 0;  // Stores the last time the mode was updated
const long interval = 5000;       // Interval to change mode (15 seconds)

// LEDController Instanzen
//                                ledCount,   ledPin, animMode, brightness, speed, animRunDuration);
LEDController ledControllerGandalf(LED_COUNT_GANDALF, LED_GANDALF, FX_MODE_RAINBOW_CYCLE,   LEDANIMBRIGHTNESKAMMUNDSCHWERT,        LEDANIMSPEED,   LEDANIMDURATION);

void setup() {

    #ifdef DEBUG
        Serial.begin(9600);
    #endif
  ledControllerGandalf.init();
  ledControllerGandalf.start();
}  

void loop() {
    unsigned long currentMillis = millis();  

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Zufälligen Effekt für Schwert, Kamm und Main auswählen
        int gandalfEffekt = ledControllerGandalf.getBalrogHitEffect();  // Beispiel für BalrogHit-Effekt


        // Setze die Effekte für die jeweiligen Controller
        //stops the old animation if still running and starts the new one with the according timer
        ledControllerGandalf.setMode(gandalfEffekt);

        // Ausgabe der aktuellen Effekte
        DEBUG_PRINT("Gandalf Effekt: ");
        DEBUG_PRINTLN(ledControllerGandalf.getEffectName(gandalfEffekt));
        DEBUG_PRINTLN("_____________________________________________________");        

     
    }

    // Dienste zur kontinuierlichen Verarbeitung der Animationen
    ledControllerGandalf.service();

}
