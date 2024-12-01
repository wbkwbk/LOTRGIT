#include "SoundFileManager.h"
#include <Arduino.h>

// Constructor
SoundFileManager::SoundFileManager() {
  // Initialisierung könnte hier erfolgen, falls nötig
}

// Helferfunktion zum zufälligen Auswählen eines Effekts aus einer Liste
const char* SoundFileManager::getRandomSound(const char* soundList[], bool usedList[], int listSize) {
  int availableCount = 0;

  // Zählen, wie viele Sounds noch verfügbar sind
  for (int i = 0; i < listSize; i++) {
    if (!usedList[i]) {
      availableCount++;
    }
  }

  // Wenn keine verfügbaren Sounds mehr übrig sind, Liste zurücksetzen
  if (availableCount == 0) {
    resetUsedList(usedList, listSize);
  }

  // Zufällig einen nicht verwendeten Sound auswählen
  int randomIndex;
  do {
    randomIndex = random(0, listSize);
  } while (usedList[randomIndex]);

  // Markieren, dass der Sound verwendet wurde
  usedList[randomIndex] = true;

  return soundList[randomIndex];
}

// Methode zum Zurücksetzen der verwendeten Liste
void SoundFileManager::resetUsedList(bool usedList[], int listSize) {
  for (int i = 0; i < listSize; i++) {
    usedList[i] = false;  // Alle Einträge auf "nicht verwendet" setzen
  }
}

// Methoden für jede Liste, die jeweils ein zufälliges Element zurückgeben

const char* SoundFileManager::getBalrogHitEffect() {
  return getRandomSound(balrogHitSounds, balrogHitUsed, BALROGHIT_COUNT);
}

const char* SoundFileManager::getBalrogOpenRampsEffect() {
  return getRandomSound(balrogOpenRampsSounds, balrogOpenRampsUsed, BALROGOPENRAMPS_COUNT);
}

const char* SoundFileManager::getBalrogClosedRampsEffect() {
  return getRandomSound(balrogClosedRampsSounds, balrogClosedRampsUsed, BALROGCLOSEDRAMPS_COUNT);
}

const char* SoundFileManager::getBalrogOpenLeftOrbitEffect() {
  return getRandomSound(balrogOpenLeftOrbitSounds, balrogOpenLeftOrbitUsed, BALROGOPENLEFTORBIT_COUNT);
}

const char* SoundFileManager::getBalrogClosedLeftOrbitEffect() {
  return getRandomSound(balrogClosedLeftOrbitSounds, balrogClosedLeftOrbitUsed, BALROGCLOSEDLEFTORBIT_COUNT);
}

const char* SoundFileManager::getBalrogClosedEffect() {
  return getRandomSound(balrogClosedSounds, balrogClosedUsed, BALROGCLOSED_COUNT);
}
