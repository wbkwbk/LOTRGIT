#include "Ripples.h"

Ripples::Ripples()
    : max_bright(128), currentPalette(OceanColors_p), targetPalette(OceanColors_p), effectRunning(false) {
    // Konstruktor - Initialisierung der Standardwerte
}

void Ripples::setup() {
    Serial.begin(115200);                                                      // Initialisierung des seriellen Monitors
    delay(1000);                                                                // Verzögerung zum Starten

    LEDS.setBrightness(max_bright);                                            // Maximale Helligkeit einstellen
    LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);               // Initialisierung der LEDs (für WS2812)
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);                           // Stromversorgung für LEDs (5V, 1A)
}

void Ripples::loop() {
    if (effectRunning) {
        EVERY_N_MILLISECONDS(50) {                                              // Palette-Übergang alle 50 ms
            uint8_t maxChanges = 24;
            nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);  // Glatter Farbübergang
        }

        EVERY_N_SECONDS(5) {
            SetupMySimilar4Palette();                                           // Ändert alle 5 Sekunden die Farbpalette
        }

        EVERY_N_MILLIS(50) {                                                   // Alle 50 ms wird der Ripple-Effekt aufgerufen
            rippless();                                                         // Ripple-Effekt ausführen
        }

        if (millis() - effectStartTime >= 10000) {                              // Stoppe nach 10 Sekunden
            stopEffect();
        }

        FastLED.show();                                                         // Zeigt das Ergebnis an
    }
}

void Ripples::startEffect() {
    effectStartTime = millis();  // Startzeit speichern
    effectRunning = true;         // Effekt als laufend markieren
}

void Ripples::stopEffect() {
    effectRunning = false;        // Effekt stoppen
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // Alle LEDs ausschalten
    FastLED.show();               // LEDs aktualisieren
}

bool Ripples::isEffectRunning() {
    return effectRunning;  // Gibt zurück, ob der Effekt läuft
}

void Ripples::rippless() {
    // Prüfen, ob ein Ripple abgelaufen ist und wenn ja, einen neuen erzeugen
    for (int i = 0; i < maxRipples; i += 2) {
        if (random8() > 224 && !ripples[i].exist) {
            ripples[i].Init(192, 10);                                           // Ripple initialisieren (Fade und MaxLife)
            ripples[i + 1] = ripples[i];                                        // Spiegeln des Ripples (Position bleibt gleich)
            ripples[i + 1].velocity *= -1;                                      // Die andere Hälfte des Ripples bewegt sich in die entgegengesetzte Richtung
        }
    }

    // Bewege und zeichne jedes Ripple
    for (int i = 0; i < maxRipples; i++) {
        if (ripples[i].exist) {
            leds[ripples[i].pos] = ColorFromPalette(currentPalette, ripples[i].color, ripples[i].brightness, LINEARBLEND);
            ripples[i].Move();  // Ripple bewegen
        }
    }

    fadeToBlackBy(leds, NUM_LEDS, 160);  // LEDs langsam verblassen
}

void Ripples::SetupMySimilar4Palette() {
    uint8_t thishue = random8();  // Generiere einen zufälligen Hue-Wert

    // Definiere eine Palette mit benachbarten Farben
    targetPalette = CRGBPalette16(
        CHSV(thishue + random8(32), 255, random8(128, 255)),
        CHSV(thishue + random8(32), 255, random8(192, 255)),
        CHSV(thishue + random8(32), 192, random8(192, 255)),
        CHSV(thishue + random8(32), 255, random8(128, 255))
    );
}

// Ripple-Struktur-Methoden

void Ripples::Ripple::Move() {
    pos += velocity;
    life++;

    // Bouncing an den Enden des Stripes
    if (pos > NUM_LEDS - 1) {
        velocity *= -1;
        pos = NUM_LEDS - 1;
    }

    if (pos < 0) {
        velocity *= -1;
        pos = 0;
    }

    // Helligkeit anpassen
    brightness = scale8(brightness, fade);

    // Ripple "sterben" lassen, wenn seine Lebensdauer überschritten ist
    if (life > maxLife) exist = false;
}

void Ripples::Ripple::Init(uint8_t Fade, uint8_t MaxLife) {
    pos = random8(NUM_LEDS / 8, NUM_LEDS - NUM_LEDS / 8);  // Ripple startet nicht zu nah am Rand
    velocity = 1;  // Ripple geht nach vorne (Richtung +1)
    life = 0;      // Leben beginnt bei 0
    maxLife = MaxLife;  // Maximallebensdauer
    exist = true;  // Ripple existiert zu Beginn
    brightness = 255;  // Maximale Helligkeit
    color = millis();  // Initialisiere Farbwert mit Zeit (HUE)
    fade = Fade;  // Fade-Wert
}
