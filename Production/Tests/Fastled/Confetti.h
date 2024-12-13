#ifndef CONFETTI_H
#define CONFETTI_H

#include "FastLED.h"

// Definiere die Konstanten
#define LED_DT 5         // Data Pin für den Strip
//#define LED_CK 11         // Clock Pin für den Strip
#define COLOR_ORDER BGR   // Farborder
#define LED_TYPE WS2812B   // Typ des LED-Streifens
#define NUM_LEDS 50       // Anzahl der LEDs

class Confetti {
public:
    Confetti();                       // Konstruktor
    void setup();                     // Setup-Funktion
    void loop();                      // Loop-Funktion
    void ChangeMe();                  // Wechselnde Einstellungen
    void confetti();                  // Hauptfunktion für den Confetti-Effekt

private:
    uint8_t max_bright;               // Maximale Helligkeit
    uint8_t thisfade;                 // Fade-Geschwindigkeit
    int thishue;                      // Start-Hue
    uint8_t thisinc;                  // Hue-Inkrement
    uint8_t thissat;                  // Sättigung
    uint8_t thisbri;                  // Helligkeit
    int huediff;                      // Farbunterschied
    uint8_t thisdelay;                // Verzögerung für die Anzeige
    unsigned long previousMillis;     // vorherige Zeit für das Update
    CRGB leds[NUM_LEDS];              // LED Array
};

#endif // CONFETTI_H
