#include <Arduino.h>
#include "SoundFileManager.h"

SoundFileManager soundManager;

unsigned long previousMillis = 0;  // Speichert die letzte Zeit
const long interval = 5000;        // 5 Sekunden Intervall

void setup() {
  Serial.begin(9600);  // Seriellen Monitor initialisieren
}

void loop() {
  unsigned long currentMillis = millis();  // Holen der aktuellen Zeit

  if (currentMillis - previousMillis >= interval) {
    // Alle 15 Sekunden einen neuen Effekt wählen
    previousMillis = currentMillis;

    // Zufällig einen der 6 Effekte auswählen
    int randomEffect = random(0, 6);

    const char* selectedSound;
    switch (randomEffect) {
      case 0:
        selectedSound = soundManager.getBalrogHitEffect();
        break;
      case 1:
        selectedSound = soundManager.getBalrogOpenRampsEffect();
        break;
      case 2:
        selectedSound = soundManager.getBalrogClosedRampsEffect();
        break;
      case 3:
        selectedSound = soundManager.getBalrogOpenLeftOrbitEffect();
        break;
      case 4:
        selectedSound = soundManager.getBalrogClosedLeftOrbitEffect();
        break;
      case 5:
        selectedSound = soundManager.getBalrogClosedEffect();
        break;
    }

    // Ausgabe des gewählten Effekts
    Serial.println(selectedSound);
  }
}
