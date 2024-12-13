#include "BlendWave.h"

BlendWave::BlendWave()
    : max_bright(128), speed(0), loc1(0), loc2(0), ran1(0), ran2(0) {
    // Konstruktor, Initialisierung von Standardwerten
}

void BlendWave::setup() {
    Serial.begin(115200);                                       // Initialisiere den Serial-Port
    delay(1000);                                                 // Weicher Start

    LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812

    FastLED.setBrightness(max_bright);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);              // FastLED Strommanagement auf 5V, 500mA setzen
}

void BlendWave::loop() {
    blendwave();  // Führt den Blendwave-Effekt aus
    FastLED.show();  // Zeigt das Ergebnis an
}

void BlendWave::blendwave() {
    // Berechne die Geschwindigkeit basierend auf einem Beat
    speed = beatsin8(6, 0, 255);

    // Berechne zwei Farben, die sich miteinander mischen
    clr1 = blend(CHSV(beatsin8(3, 0, 255), 255, 255), CHSV(beatsin8(4, 0, 255), 255, 255), speed);
    clr2 = blend(CHSV(beatsin8(4, 0, 255), 255, 255), CHSV(beatsin8(3, 0, 255), 255, 255), speed);

    // Berechne eine Position basierend auf einem anderen Beat
    loc1 = beatsin8(10, 0, NUM_LEDS - 1);

    // Fülle den LED-Array mit einem Farbverlauf
    fill_gradient_RGB(leds, 0, clr2, loc1, clr1);
    fill_gradient_RGB(leds, loc1, clr2, NUM_LEDS - 1, clr1);
}
