#ifndef BLENDWAVE_H
#define BLENDWAVE_H

#include "FastLED.h"

// Definiere die Konstanten
#define LED_DT 5         // Data Pin für den Strip
#define LED_CK 11         // Clock Pin für den Strip (APA102, WS2801)
#define COLOR_ORDER BGR   // Farborder
#define LED_TYPE WS2812B   // Typ des LED-Streifens
#define NUM_LEDS 60       // Anzahl der LEDs

class BlendWave {
public:
    BlendWave();                       // Konstruktor
    void setup();                       // Setup-Funktion
    void loop();                        // Loop-Funktion
    void blendwave();                   // Blendwave-Effekt

private:
    uint8_t max_bright;                 // Maximale Helligkeit
    CRGB leds[NUM_LEDS];                // LED Array
    CRGB clr1, clr2;                    // Farbvariablen
    uint8_t speed;                      // Geschwindigkeit
    uint8_t loc1, loc2;                 // Positionen der Wellen
    uint8_t ran1, ran2;                 // Zufallswerte
};

#endif // BLENDWAVE_H
