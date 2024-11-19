#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <WS2812FX.h>

class LEDController {
public:
    LEDController(uint16_t ledCount, uint8_t ledPin, uint8_t animMode, uint8_t brightness, uint16_t speed, uint16_t animRunDuration);
    void start();
    void service();
    void init();
    void setBrightness(int brightness); 
    void setSpeed(int speed);
    void setMode(int mode);

private:
    WS2812FX ws2812fx;
    uint16_t animRunDuration_;
    uint8_t brightness_;
    uint8_t mode_;
    uint16_t speed_;
    unsigned  animStarttime;
    bool isAnimrunning;

};

#endif