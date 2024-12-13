#include "RainbowMarch.h"

RainbowMarch::RainbowMarch()
    : max_bright(255) {
    // Konstruktor, Initialisierung von Standardwerten
}

void RainbowMarch::setup() {
    Serial.begin(115200);                                      // Initialisiere den seriellen Monitor
    delay(1000);                                                // Soft-Start

    LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812

    FastLED.setBrightness(max_bright);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);            // FastLED Strommanagement auf 5V, 1000mA setzen
}

void RainbowMarch::loop() {
    rainbow_march(200, 10);  // Führt den Rainbow March Effekt aus
    FastLED.show();          // Zeigt das Ergebnis an
}

void RainbowMarch::rainbow_march(uint8_t thisdelay, uint8_t deltahue) {
    uint8_t thishue = millis() * (255 - thisdelay) / 255;       // Berechnet den Hue-Wert basierend auf der Zeit und dem Delay-Wert

    // Alternativ könntest du auch einen Beat verwenden:
    // thishue = beat8(50);                                      // FastLED sawtooth generator
    // thishue = beatsin8(50, 0, 255);                           // Beat mit veränderlicher Geschwindigkeit

    fill_rainbow(leds, NUM_LEDS, thishue, deltahue);            // Füllt den LED-Array mit einem Regenbogen
}
