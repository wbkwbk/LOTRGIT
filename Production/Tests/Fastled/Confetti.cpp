#include "Confetti.h"

Confetti::Confetti()
    : max_bright(128), thisfade(8), thishue(50), thisinc(1),
      thissat(100), thisbri(255), huediff(256), thisdelay(5), previousMillis(0) {
    // Konstruktor, Initialisierung von Standardwerten
}

void Confetti::setup() {
    delay(1000);  // Power-up safety delay
    Serial.begin(115200);

    // LEDs einrichten (für APA102 oder WS2801)
    LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);    // Use this for WS2812B

    FastLED.setBrightness(max_bright);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); // FastLED Strommanagement auf 5V, 500mA setzen
}

void Confetti::loop() {
    ChangeMe();  // Überprüft, ob Änderungen vorgenommen werden müssen

    EVERY_N_MILLISECONDS(thisdelay) {
        confetti();  // FastLED basiertes nicht-blockierendes Delay
    }
    FastLED.show();  // LEDs anzeigen
}

void Confetti::confetti() {
    fadeToBlackBy(leds, NUM_LEDS, thisfade);  // LEDs verblassen
    int pos = random16(NUM_LEDS);             // Zufällige Position
    leds[pos] += CHSV((thishue + random16(huediff)) / 4, thissat, thisbri);  // Zufällige Farbe hinzufügen
    thishue = thishue + thisinc;              // Hue Inkrement
}

void Confetti::ChangeMe() {
    uint8_t secondHand = (millis() / 1000) % 15;  // Jede Sekunde ändern
    static uint8_t lastSecond = 99;               // Für Entprellung

    if (lastSecond != secondHand) {
        lastSecond = secondHand;
        switch (secondHand) {
            case 0:
                thisinc = 1; thishue = 192; thissat = 255; thisfade = 2; huediff = 256;
                break;
            case 5:
                thisinc = 2; thishue = 128; thisfade = 8; huediff = 64;
                break;
            case 10:
                thisinc = 1; thishue = random16(255); thisfade = 1; huediff = 16;
                break;
            case 15:
                break; // Kein Wechsel
        }
    }
}
