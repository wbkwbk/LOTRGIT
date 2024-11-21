#include "SoundFileManager.h"
#include <Arduino.h>

// Constructor
SoundFileManager::SoundFileManager() {
  // You could initialize other members here if needed
}

// Returns a random Gandalf sound file
const char* SoundFileManager::getGandalfSound() {
  int randomIndex = random(0, GANDALF_SOUND_COUNT);  // Random index between 0 and 2
  return gandalfSounds[randomIndex];
}

// Returns a random other sound file
const char* SoundFileManager::getOtherSound() {
  int randomIndex = random(0, OTHER_SOUND_COUNT);  // Random index between 0 and 2
  return otherSounds[randomIndex];
}