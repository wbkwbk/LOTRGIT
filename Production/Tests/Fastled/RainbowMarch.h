#ifndef RAINBOW_MARCH_H
#define RAINBOW_MARCH_H

#include "FastLED.h"

// Definiere die Konstanten
#define LED_DT 6         // Data Pin für den Strip
#define LED_CK 11         // Clock Pin für den Strip (APA102, WS2801)
#define COLOR_ORDER GRB   // Farborder
#define LED_TYPE WS2812B   // Typ des LED-Streifens
#define NUM_LEDS 120       // Anzahl der LEDs

class RainbowMarch {
public:
    RainbowMarch();                       // Konstruktor
    void setup();                          // Setup-Funktion
    void loop();                           // Loop-Funktion
    void rainbow_march(uint8_t thisdelay, uint8_t deltahue); // Rainbow March Effekt

private:
    uint8_t max_bright;                    // Maximale Helligkeit
    CRGB leds[NUM_LEDS];                   // LED Array
};

#endif // RAINBOW_MARCH_H
