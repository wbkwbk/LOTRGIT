#ifndef GandalfMagicWand_h
#define GandalfMagicWand_h

#include "Arduino.h"

class GandalfMagicWand {
  public:
    // Constructor to initialize the pin where the LED is connected
    GandalfMagicWand(int pin);
    
    // Method to start the magic lightning effect for a specific duration
    void start(int duration);

    // Call this method in the loop to update the lightning effect
    void update();
    void setBalrogOpenState(boolean balrogstate);

  private:
    int _ledPin;           // LED pin number
    unsigned long _startMillis;  // Time when the effect started
    int _duration;         // Duration for the effect in milliseconds
    unsigned long _lastFlashMillis;  // Last time the LED was flashed
    bool _ledState;        // Current state of the LED (on or off)
    int _flashDuration;    // Duration for each flash
    int _pwmValue;
    bool isBalrogOpen = false;    
};

#endif