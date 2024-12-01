#include "LEDController.h"

LEDController::LEDController(uint16_t ledCount, uint8_t ledPin, uint8_t animMode, uint8_t brightness, uint16_t speed, uint16_t animRunDuration) :
    ws2812fx(ledCount, ledPin, NEO_GRB + NEO_KHZ800),
    animRunDuration_(animRunDuration),
    brightness_(brightness),
    mode_(animMode),
    speed_(speed) {
}

void LEDController::init() {
    ws2812fx.init();
    ws2812fx.setBrightness(brightness_);
    ws2812fx.setSpeed(speed_);
    ws2812fx.setMode(mode_);
    isAnimrunning = false;
}

void LEDController::start() {
    animStarttime = millis();
    ws2812fx.start();
    isAnimrunning = true;
}

void LEDController::setBrightness(int brightness) {
    brightness_ = brightness;
    ws2812fx.setBrightness(brightness_);
}

void LEDController::setSpeed(int speed) {
    speed_ = speed;
    ws2812fx.setSpeed(speed_);
}

/*sets a new mode and starts the animation*/
void LEDController::setMode(int mode) {
    mode_ = mode;
    ws2812fx.stop();
    ws2812fx.setMode(mode_);
    start();

}

void LEDController::setBalrogOpenState(boolean balrogstate) {
    isBalrogOpen = balrogstate;
}

void LEDController::stop() {
    ws2812fx.stop();
}

void LEDController::service() {
    if (isAnimrunning) {
        //during balrog open do never stop the animation
        if (millis() - animStarttime < animRunDuration_ || isBalrogOpen) {
            ws2812fx.service();
        } else {
            ws2812fx.stop();
            isAnimrunning = false;
        }
    }
}

// Modified function: accepts const int[] for effects, non-const bool[] for usage tracking
int LEDController::getRandomEffect(const int effects[], bool used[], int size) {
    // Check if all effects have been used and reset if necessary
    bool allUsed = true;
    for (int i = 0; i < size; ++i) {
        if (!used[i]) {
            allUsed = false;
            break;
        }
    }

    if (allUsed) {
        resetEffectUsage(used, size);
    }

    // Pick a random effect that hasn't been used yet
    int effectIndex;
    do {
        effectIndex = random(size);
    } while (used[effectIndex]);

    used[effectIndex] = true;
    return effects[effectIndex];
}

void LEDController::resetEffectUsage(bool used[], int size) {
    for (int i = 0; i < size; ++i) {
        used[i] = false;
    }
}

// Methods to get a random effect from each list
int LEDController::getBalrogHitEffect() {
    return getRandomEffect(balrogHitEffects, usedBalrogHit, 7);
}

int LEDController::getBalrogOpenRampsEffect() {
    return getRandomEffect(balrogOpenRampsEffects, usedBalrogOpenRamps, 15);
}

int LEDController::getBalrogClosedRampsEffect() {
    return getRandomEffect(balrogClosedRampsEffects, usedBalrogClosedRamps, 15);
}

int LEDController::getBalrogOpenLeftOrbitEffect() {
    return getRandomEffect(balrogOpenLeftOrbitEffects, usedBalrogOpenLeftOrbit, 10);
}

int LEDController::getBalrogClosedLeftOrbitEffect() {
    return getRandomEffect(balrogClosedLeftOrbitEffects, usedBalrogClosedLeftOrbit, 10);
}

int LEDController::getBalrogClosedEffect() {
    return getRandomEffect(balrogClosedEffects, usedBalrogClosed, 2);
}


const char* LEDController::getEffectName(int effect) {
    switch (effect) {
        case FX_MODE_STATIC:                   return "STATIC";
        case FX_MODE_BLINK:                    return "BLINK";
        case FX_MODE_BREATH:                   return "BREATH";
        case FX_MODE_COLOR_WIPE:               return "COLOR_WIPE";
        case FX_MODE_COLOR_WIPE_INV:           return "COLOR_WIPE_INV";
        case FX_MODE_COLOR_WIPE_REV:           return "COLOR_WIPE_REV";
        case FX_MODE_COLOR_WIPE_REV_INV:       return "COLOR_WIPE_REV_INV";
        case FX_MODE_COLOR_WIPE_RANDOM:        return "COLOR_WIPE_RANDOM";
        case FX_MODE_RANDOM_COLOR:             return "RANDOM_COLOR";
        case FX_MODE_SINGLE_DYNAMIC:           return "SINGLE_DYNAMIC";
        case FX_MODE_MULTI_DYNAMIC:            return "MULTI_DYNAMIC";
        case FX_MODE_RAINBOW:                 return "RAINBOW";
        case FX_MODE_RAINBOW_CYCLE:           return "RAINBOW_CYCLE";
        case FX_MODE_SCAN:                    return "SCAN";
        case FX_MODE_DUAL_SCAN:               return "DUAL_SCAN";
        case FX_MODE_FADE:                    return "FADE";
        case FX_MODE_THEATER_CHASE:           return "THEATER_CHASE";
        case FX_MODE_THEATER_CHASE_RAINBOW:   return "THEATER_CHASE_RAINBOW";
        case FX_MODE_RUNNING_LIGHTS:          return "RUNNING_LIGHTS";
        case FX_MODE_TWINKLE:                 return "TWINKLE";
        case FX_MODE_TWINKLE_RANDOM:          return "TWINKLE_RANDOM";
        case FX_MODE_TWINKLE_FADE:            return "TWINKLE_FADE";
        case FX_MODE_TWINKLE_FADE_RANDOM:     return "TWINKLE_FADE_RANDOM";
        case FX_MODE_SPARKLE:                 return "SPARKLE";
        case FX_MODE_FLASH_SPARKLE:           return "FLASH_SPARKLE";
        case FX_MODE_HYPER_SPARKLE:           return "HYPER_SPARKLE";
        case FX_MODE_STROBE:                  return "STROBE";
        case FX_MODE_STROBE_RAINBOW:          return "STROBE_RAINBOW";
        case FX_MODE_MULTI_STROBE:            return "MULTI_STROBE";
        case FX_MODE_BLINK_RAINBOW:           return "BLINK_RAINBOW";
        case FX_MODE_CHASE_WHITE:             return "CHASE_WHITE";
        case FX_MODE_CHASE_COLOR:             return "CHASE_COLOR";
        case FX_MODE_CHASE_RANDOM:            return "CHASE_RANDOM";
        case FX_MODE_CHASE_RAINBOW:           return "CHASE_RAINBOW";
        case FX_MODE_CHASE_FLASH:             return "CHASE_FLASH";
        case FX_MODE_CHASE_FLASH_RANDOM:      return "CHASE_FLASH_RANDOM";
        case FX_MODE_CHASE_RAINBOW_WHITE:     return "CHASE_RAINBOW_WHITE";
        case FX_MODE_CHASE_BLACKOUT:          return "CHASE_BLACKOUT";
        case FX_MODE_CHASE_BLACKOUT_RAINBOW:  return "CHASE_BLACKOUT_RAINBOW";
        case FX_MODE_COLOR_SWEEP_RANDOM:      return "COLOR_SWEEP_RANDOM";
        case FX_MODE_RUNNING_COLOR:           return "RUNNING_COLOR";
        case FX_MODE_RUNNING_RED_BLUE:        return "RUNNING_RED_BLUE";
        case FX_MODE_RUNNING_RANDOM:          return "RUNNING_RANDOM";
        case FX_MODE_LARSON_SCANNER:          return "LARSON_SCANNER";
        case FX_MODE_COMET:                   return "COMET";
        case FX_MODE_FIREWORKS:               return "FIREWORKS";
        case FX_MODE_FIREWORKS_RANDOM:        return "FIREWORKS_RANDOM";
        case FX_MODE_MERRY_CHRISTMAS:         return "MERRY_CHRISTMAS";
        case FX_MODE_FIRE_FLICKER:            return "FIRE_FLICKER";
        case FX_MODE_FIRE_FLICKER_SOFT:       return "FIRE_FLICKER_SOFT";
        case FX_MODE_FIRE_FLICKER_INTENSE:    return "FIRE_FLICKER_INTENSE";
        case FX_MODE_CIRCUS_COMBUSTUS:        return "CIRCUS_COMBUSTUS";
        case FX_MODE_HALLOWEEN:               return "HALLOWEEN";
        case FX_MODE_BICOLOR_CHASE:           return "BICOLOR_CHASE";
        case FX_MODE_TRICOLOR_CHASE:          return "TRICOLOR_CHASE";
        case FX_MODE_TWINKLEFOX:              return "TWINKLEFOX";
        case FX_MODE_RAIN:                    return "RAIN";
        case FX_MODE_CUSTOM:                  return "CUSTOM";
        default:                              return "UNKNOWN";
    }
}