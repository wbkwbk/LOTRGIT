#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <WS2812FX.h>

class LEDController {
public:
    LEDController(uint16_t ledCount, uint8_t ledPin, uint8_t animMode, uint8_t brightness, uint16_t speed, uint16_t animRunDuration);
    void start();
    void stop();
    void service();
    void init();
    void setBrightness(int brightness);
    void setSpeed(int speed);
    void setMode(int mode);
    const char* getEffectName(int effect);
    
    // Methods to get random effects
    int getBalrogHitEffect();
    int getBalrogOpenRampsEffect();
    int getBalrogClosedRampsEffect();
    int getBalrogOpenLeftOrbitEffect();
    int getBalrogClosedLeftOrbitEffect();
    int getBalrogClosedEffect();

private:
    WS2812FX ws2812fx;
    uint16_t animRunDuration_;
    uint8_t brightness_;
    uint8_t mode_;
    uint16_t speed_;
    unsigned long animStarttime;
    bool isAnimrunning;

    // Lists of effects
    const int balrogHitEffects[3] = {FX_MODE_BLINK, FX_MODE_COLOR_WIPE, FX_MODE_RAINBOW};
    const int balrogOpenRampsEffects[4] = {FX_MODE_SCAN, FX_MODE_FADE, FX_MODE_RAINBOW_CYCLE, FX_MODE_BLINK};
    const int balrogClosedRampsEffects[3] = {FX_MODE_RUNNING_LIGHTS, FX_MODE_COMET, FX_MODE_SPARKLE};
    const int balrogOpenLeftOrbitEffects[2] = {FX_MODE_FIREWORKS, FX_MODE_FIRE_FLICKER};
    const int balrogClosedLeftOrbitEffects[2] = {FX_MODE_THEATER_CHASE, FX_MODE_CHASE_RAINBOW};
    const int balrogClosedEffects[3] = {FX_MODE_STROBE, FX_MODE_COLOR_SWEEP_RANDOM, FX_MODE_TWINKLE};
    
    // Helper arrays to track which effects have been used
    bool usedBalrogHit[3] = {false, false, false};
    bool usedBalrogOpenRamps[4] = {false, false, false, false};
    bool usedBalrogClosedRamps[3] = {false, false, false};
    bool usedBalrogOpenLeftOrbit[2] = {false, false};
    bool usedBalrogClosedLeftOrbit[2] = {false, false};
    bool usedBalrogClosed[3] = {false, false, false};
    
    // Function to get a random effect from a list
    int getRandomEffect(const int effects[], bool used[], int size);
    void resetEffectUsage(bool used[], int size);

};

#endif
