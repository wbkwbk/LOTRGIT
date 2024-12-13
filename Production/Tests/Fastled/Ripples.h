#ifndef RIPPLES_H
#define RIPPLES_H

#include "FastLED.h"

// Konstanten und Definitionsbereiche
#define LED_DT 2                                                               // Data Pin für WS2812
#define LED_CK 11                                                              // Clock Pin für WS2801 oder APA102
#define COLOR_ORDER GRB                                                        // Farbordnung (GRB für WS2812)
#define LED_TYPE WS2812                                                        // LED Typ (z. B. WS2812, WS2801)
#define NUM_LEDS 40                                                            // Anzahl der LEDs

#define maxRipples 6                                                           // Maximale Anzahl der Ripples (mindestens 2)

class Ripples {
public:
    Ripples();                                                                // Konstruktor
    void setup();                                                              // Setup der LEDs
    void loop();                                                               // Loop Funktion, wird ständig aufgerufen
    void startEffect();                                                        // Startet den Ripple-Effekt
    void stopEffect();                                                         // Stoppt den Ripple-Effekt
    bool isEffectRunning();                                                    // Überprüft, ob der Effekt läuft

private:
    uint8_t max_bright;                                                       // Maximale Helligkeit
    CRGB leds[NUM_LEDS];                                                      // Array der LEDs
    CRGBPalette16 currentPalette;                                              // Aktuelle Farbpalette
    CRGBPalette16 targetPalette;                                               // Zielpalette für den Farbwechsel

    unsigned long effectStartTime;                                             // Startzeit des Effekts
    bool effectRunning;                                                        // Flag, ob der Effekt läuft

    struct Ripple {                                                            // Ripple Struktur (Reko Meriö)
        uint8_t brightness;                                                    // Helligkeit
        int8_t color;                                                          // Farbe
        int16_t pos;                                                           // Position des Ripples
        int8_t velocity;                                                       // Richtung des Ripples (1 oder -1)
        uint8_t life;                                                          // Leben des Ripples
        uint8_t maxLife;                                                       // Maximale Lebensdauer des Ripples
        uint8_t fade;                                                          // Fading-Effekt
        bool exist;                                                            // Existiert das Ripple?

        void Move();                                                           // Bewegung des Ripples
        void Init(uint8_t Fade, uint8_t MaxLife);                               // Initialisierung des Ripples
    };

    Ripple ripples[maxRipples];                                                 // Array der Ripples

    void rippless();                                                           // Diese Methode muss hier deklariert werden
    void SetupMySimilar4Palette();                                              // Diese Methode muss hier deklariert werden
};

#endif // RIPPLES_H
