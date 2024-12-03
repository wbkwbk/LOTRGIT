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
    int getGandalfBalrogHitEffect();
    int getGandalfRampsEffect();
    int getGandalfLeftOrbitEffect();
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

    static const int BALROGHIT_COUNT = 7;
    static const int BALROGCLOSED_COUNT = 2;    
    static const int BALROGOPENRAMPS_COUNT = 15;
    static const int BALROGCLOSEDRAMPS_COUNT = 15;
    static const int BALROGOPENLEFTORBIT_COUNT = 10;
    static const int BALROGCLOSEDLEFTORBIT_COUNT = 10;


    static const int GANDALF_BALROGHIT_COUNT = 9;
    static const int GANDALF_RAMPS_COUNT = 10;
    static const int GANDALF_LEFTORBIT_COUNT = 8;


    // Lists of effects
    const int gandalfbalrogHitEffects[GANDALF_BALROGHIT_COUNT] = {FX_MODE_BLINK, FX_MODE_FADE, FX_MODE_SPARKLE, FX_MODE_HYPER_SPARKLE, FX_MODE_STROBE, FX_MODE_STROBE_RAINBOW, FX_MODE_MULTI_STROBE, FX_MODE_FIREWORKS, FX_MODE_RAIN};
    const int gandalfRampsEffects[GANDALF_RAMPS_COUNT] = {FX_MODE_COLOR_WIPE_INV, FX_MODE_COLOR_WIPE_REV, FX_MODE_COLOR_WIPE_REV, FX_MODE_COLOR_WIPE_REV_INV, FX_MODE_COLOR_WIPE_RANDOM, FX_MODE_RANDOM_COLOR, FX_MODE_RAINBOW, FX_MODE_SCAN, FX_MODE_DUAL_SCAN, FX_MODE_RUNNING_LIGHTS};
    const int gandalfLeftOrbitEffects[GANDALF_LEFTORBIT_COUNT] = {FX_MODE_CHASE_COLOR, FX_MODE_CHASE_BLACKOUT, FX_MODE_CHASE_BLACKOUT_RAINBOW, FX_MODE_COLOR_SWEEP_RANDOM, FX_MODE_LARSON_SCANNER, FX_MODE_COMET, FX_MODE_FIRE_FLICKER_INTENSE, FX_MODE_TWINKLEFOX,};
    const int balrogHitEffects[BALROGHIT_COUNT] = {FX_MODE_BLINK , FX_MODE_STROBE , FX_MODE_MULTI_STROBE,FX_MODE_FIREWORKS , FX_MODE_FIRE_FLICKER , FX_MODE_FIRE_FLICKER_INTENSE , FX_MODE_TWINKLEFOX };
    const int balrogClosedEffects[BALROGCLOSED_COUNT] = {FX_MODE_CHASE_FLASH , FX_MODE_CHASE_BLACKOUT};
    const int balrogOpenRampsEffects[BALROGOPENRAMPS_COUNT] = {FX_MODE_BREATH , FX_MODE_COLOR_WIPE , FX_MODE_COLOR_WIPE_INV , FX_MODE_COLOR_WIPE_REV , FX_MODE_COLOR_WIPE_REV_INV ,FX_MODE_COLOR_WIPE_RANDOM ,FX_MODE_SCAN ,FX_MODE_DUAL_SCAN ,FX_MODE_FADE ,FX_MODE_RUNNING_LIGHTS ,FX_MODE_RUNNING_COLOR ,FX_MODE_LARSON_SCANNER ,FX_MODE_COMET ,FX_MODE_BICOLOR_CHASE ,FX_MODE_TRICOLOR_CHASE };
    const int balrogClosedRampsEffects[BALROGCLOSEDRAMPS_COUNT] = {FX_MODE_BREATH , FX_MODE_COLOR_WIPE , FX_MODE_COLOR_WIPE_INV , FX_MODE_COLOR_WIPE_REV , FX_MODE_COLOR_WIPE_REV_INV ,FX_MODE_COLOR_WIPE_RANDOM ,FX_MODE_SCAN ,FX_MODE_DUAL_SCAN ,FX_MODE_FADE ,FX_MODE_RUNNING_LIGHTS ,FX_MODE_RUNNING_COLOR ,FX_MODE_LARSON_SCANNER ,FX_MODE_COMET ,FX_MODE_BICOLOR_CHASE ,FX_MODE_TRICOLOR_CHASE };
    const int balrogOpenLeftOrbitEffects[BALROGOPENLEFTORBIT_COUNT] = {FX_MODE_RAINBOW , FX_MODE_RAINBOW_CYCLE ,FX_MODE_THEATER_CHASE ,FX_MODE_THEATER_CHASE_RAINBOW, FX_MODE_TWINKLE ,FX_MODE_FLASH_SPARKLE ,FX_MODE_CHASE_COLOR ,FX_MODE_CHASE_RAINBOW ,FX_MODE_COLOR_SWEEP_RANDOM ,FX_MODE_MERRY_CHRISTMAS };
    const int balrogClosedLeftOrbitEffects[BALROGCLOSEDLEFTORBIT_COUNT] = {FX_MODE_RAINBOW , FX_MODE_RAINBOW_CYCLE ,FX_MODE_THEATER_CHASE ,FX_MODE_THEATER_CHASE_RAINBOW, FX_MODE_TWINKLE ,FX_MODE_FLASH_SPARKLE ,FX_MODE_CHASE_COLOR ,FX_MODE_CHASE_RAINBOW ,FX_MODE_COLOR_SWEEP_RANDOM ,FX_MODE_MERRY_CHRISTMAS };
    
    // Helper arrays to track which effects have been used
    bool usedGandalfBalrogHit[GANDALF_BALROGHIT_COUNT] = {false, false, false, false, false, false, false, false, false};
    bool usedGandalfRamps[GANDALF_RAMPS_COUNT] = {false, false, false, false, false, false, false, false, false, false};
    bool usedGandalfLeftOrbit[GANDALF_LEFTORBIT_COUNT] = {false, false, false, false, false, false, false, false};
    bool usedBalrogHit[BALROGHIT_COUNT] = {false, false, false, false, false, false, false};
    bool usedBalrogClosed[BALROGCLOSED_COUNT] = {false, false};
    bool usedBalrogOpenRamps[BALROGOPENRAMPS_COUNT] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    bool usedBalrogClosedRamps[BALROGOPENRAMPS_COUNT] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    bool usedBalrogOpenLeftOrbit[BALROGOPENLEFTORBIT_COUNT] = {false, false, false, false, false, false, false, false, false, false};
    bool usedBalrogClosedLeftOrbit[BALROGOPENLEFTORBIT_COUNT] = {false, false, false, false, false, false, false, false, false, false};
    
    // Function to get a random effect from a list
    int getRandomEffect(const int effects[], bool used[], int size);
    void resetEffectUsage(bool used[], int size);

};

#endif
