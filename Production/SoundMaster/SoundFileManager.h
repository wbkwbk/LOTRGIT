#ifndef SOUNDFILEMANAGER_H
#define SOUNDFILEMANAGER_H

#include <Arduino.h>

class SoundFileManager {
  private:
    static const int GANDALF_SOUND_COUNT = 6;
    static const int OTHER_SOUND_COUNT = 0;

    const char* gandalfSounds[GANDALF_SOUND_COUNT] = {
	      "AWINL.mp3",
	      "CWMML.mp3",
	      "FOAT.mp3",
	      "MIIJY.mp3",
	      "PFB.mp3",
	      "TINBOT.mp3"
    };
    
    const char* otherSounds[OTHER_SOUND_COUNT] = {
    };

  public:
    // Constructor
    SoundFileManager();

    // Returns a random Gandalf sound file
    const char* getGandalfSound();

    // Returns a random other sound file
    const char* getOtherSound();
};

#endif