#include "LEDController.h"

mainLedController::mainLedController(uint16_t ledCount, uint8_t ledPin, uint8_t animMode, uint8_t brightness, uint16_t speed, uint16_t animRunDuration) :
    ws2812fx(ledCount, ledPin, NEO_GRB + NEO_KHZ800),
    animRunDuration_(animRunDuration),
    brightness_(brightness),
    mode_(animMode),
    speed_(speed) {
}

void mainLedController::init() {
    ws2812fx.init();
    ws2812fx.setBrightness(brightness_);
    ws2812fx.setSpeed(speed_);
    ws2812fx.setMode(mode_);
    isAnimrunning = false;
}

void mainLedController::start() {
    animStarttime = millis();
    ws2812fx.start();
    isAnimrunning = true;
}

void mainLedController::setBrightness(int brightness) {
    brightness_ = brightness;
    ws2812fx.setBrightness(brightness_);
}
void mainLedController::setSpeed(int speed) {
    speed_ = speed;
    ws2812fx.setSpeed(speed_);
}

void mainLedController::setMode(int mode) {
    mode_ = mode;
    ws2812fx.setMode(mode_);
}

void mainLedController::service() {
    if(isAnimrunning){
      if(millis() - animStarttime < animRunDuration_){
        ws2812fx.service();  
      }else{
        ws2812fx.stop();
        isAnimrunning = false;
      }
    }
  }