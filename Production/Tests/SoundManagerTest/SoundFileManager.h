#ifndef SOUNDFILEMANAGER_H
#define SOUNDFILEMANAGER_H

#include <Arduino.h>

class SoundFileManager {
  private:
    static const int BALROGHIT_COUNT = 5;
    static const int BALROGOPENRAMPS_COUNT = 4;
    static const int BALROGCLOSEDRAMPS_COUNT = 3;
    static const int BALROGOPENLEFTORBIT_COUNT = 3;
    static const int BALROGCLOSEDLEFTORBIT_COUNT = 4;
    static const int BALROGCLOSED_COUNT = 3;

    // Arrays für Sounddateien
    const char* balrogHitSounds[BALROGHIT_COUNT] = {
      "BalrogHit1.mp3", "BalrogHit2.mp3", "BalrogHit3.mp3", "BalrogHit4.mp3", "BalrogHit5.mp3"
    };
    const char* balrogOpenRampsSounds[BALROGOPENRAMPS_COUNT] = {
      "BalrogOpenRamp1.mp3", "BalrogOpenRamp2.mp3", "BalrogOpenRamp3.mp3", "BalrogOpenRamp4.mp3"
    };
    const char* balrogClosedRampsSounds[BALROGCLOSEDRAMPS_COUNT] = {
      "BalrogClosedRamp1.mp3", "BalrogClosedRamp2.mp3", "BalrogClosedRamp3.mp3"
    };
    const char* balrogOpenLeftOrbitSounds[BALROGOPENLEFTORBIT_COUNT] = {
      "BalrogOpenLeftOrbit1.mp3", "BalrogOpenLeftOrbit2.mp3", "BalrogOpenLeftOrbit3.mp3"
    };
    const char* balrogClosedLeftOrbitSounds[BALROGCLOSEDLEFTORBIT_COUNT] = {
      "BalrogClosedLeftOrbit1.mp3", "BalrogClosedLeftOrbit2.mp3", "BalrogClosedLeftOrbit3.mp3", "BalrogClosedLeftOrbit4.mp3"
    };
    const char* balrogClosedSounds[BALROGCLOSED_COUNT] = {
      "BalrogClosed1.mp3", "BalrogClosed2.mp3", "BalrogClosed3.mp3"
    };

    // Indizes zur Verfolgung der verwendeten Sounds
    bool balrogHitUsed[BALROGHIT_COUNT] = { false, false, false, false, false };
    bool balrogOpenRampsUsed[BALROGOPENRAMPS_COUNT] = { false, false, false, false };
    bool balrogClosedRampsUsed[BALROGCLOSEDRAMPS_COUNT] = { false, false, false };
    bool balrogOpenLeftOrbitUsed[BALROGOPENLEFTORBIT_COUNT] = { false, false, false };
    bool balrogClosedLeftOrbitUsed[BALROGCLOSEDLEFTORBIT_COUNT] = { false, false, false, false };
    bool balrogClosedUsed[BALROGCLOSED_COUNT] = { false, false, false };

  public:
    // Constructor
    SoundFileManager();

    // Methoden zum Abrufen eines zufälligen Effekts
    const char* getBalrogHitEffect();
    const char* getBalrogOpenRampsEffect();
    const char* getBalrogClosedRampsEffect();
    const char* getBalrogOpenLeftOrbitEffect();
    const char* getBalrogClosedLeftOrbitEffect();
    const char* getBalrogClosedEffect();
    
    // Helferfunktion zum zufälligen Auswählen eines Effekts
    const char* getRandomSound(const char* soundList[], bool usedList[], int listSize);
    
    // Helferfunktion zum Zurücksetzen der verwendeten Liste
    void resetUsedList(bool usedList[], int listSize);
};

#endif
