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
    void setBalrogOpenState(boolean balrogstate);
    
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
    bool isBalrogOpen = false;

    // Lists of effects
    const int balrogHitEffects[7] = {FX_MODE_BLINK , FX_MODE_STROBE , FX_MODE_MULTI_STROBE,FX_MODE_FIREWORKS , FX_MODE_FIRE_FLICKER , FX_MODE_FIRE_FLICKER_INTENSE , FX_MODE_TWINKLEFOX };
    const int balrogClosedEffects[2] = {FX_MODE_CHASE_FLASH , FX_MODE_CHASE_BLACKOUT};
    const int balrogOpenRampsEffects[15] = {FX_MODE_BREATH , FX_MODE_COLOR_WIPE , FX_MODE_COLOR_WIPE_INV , FX_MODE_COLOR_WIPE_REV , FX_MODE_COLOR_WIPE_REV_INV ,FX_MODE_COLOR_WIPE_RANDOM ,FX_MODE_SCAN ,FX_MODE_DUAL_SCAN ,FX_MODE_FADE ,FX_MODE_RUNNING_LIGHTS ,FX_MODE_RUNNING_COLOR ,FX_MODE_LARSON_SCANNER ,FX_MODE_COMET ,FX_MODE_BICOLOR_CHASE ,FX_MODE_TRICOLOR_CHASE };
    const int balrogClosedRampsEffects[15] = {FX_MODE_BREATH , FX_MODE_COLOR_WIPE , FX_MODE_COLOR_WIPE_INV , FX_MODE_COLOR_WIPE_REV , FX_MODE_COLOR_WIPE_REV_INV ,FX_MODE_COLOR_WIPE_RANDOM ,FX_MODE_SCAN ,FX_MODE_DUAL_SCAN ,FX_MODE_FADE ,FX_MODE_RUNNING_LIGHTS ,FX_MODE_RUNNING_COLOR ,FX_MODE_LARSON_SCANNER ,FX_MODE_COMET ,FX_MODE_BICOLOR_CHASE ,FX_MODE_TRICOLOR_CHASE };
    const int balrogOpenLeftOrbitEffects[10] = {FX_MODE_RAINBOW , FX_MODE_RAINBOW_CYCLE ,FX_MODE_THEATER_CHASE ,FX_MODE_THEATER_CHASE_RAINBOW, FX_MODE_TWINKLE ,FX_MODE_FLASH_SPARKLE ,FX_MODE_CHASE_COLOR ,FX_MODE_CHASE_RAINBOW ,FX_MODE_COLOR_SWEEP_RANDOM ,FX_MODE_MERRY_CHRISTMAS };
    const int balrogClosedLeftOrbitEffects[10] = {FX_MODE_RAINBOW , FX_MODE_RAINBOW_CYCLE ,FX_MODE_THEATER_CHASE ,FX_MODE_THEATER_CHASE_RAINBOW, FX_MODE_TWINKLE ,FX_MODE_FLASH_SPARKLE ,FX_MODE_CHASE_COLOR ,FX_MODE_CHASE_RAINBOW ,FX_MODE_COLOR_SWEEP_RANDOM ,FX_MODE_MERRY_CHRISTMAS };
    
    // Helper arrays to track which effects have been used
    bool usedBalrogHit[7] = {false, false, false, false, false, false, false};
    bool usedBalrogClosed[2] = {false, false};
    bool usedBalrogOpenRamps[15] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    bool usedBalrogClosedRamps[15] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    bool usedBalrogOpenLeftOrbit[10] = {false, false, false, false, false, false, false, false, false, false};
    bool usedBalrogClosedLeftOrbit[10] = {false, false, false, false, false, false, false, false, false, false};
    
    // Function to get a random effect from a list
    int getRandomEffect(const int effects[], bool used[], int size);
    void resetEffectUsage(bool used[], int size);

};

#endif
