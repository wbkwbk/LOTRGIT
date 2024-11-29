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
}
void LEDController::setSpeed(int speed) {
    speed_ = speed;
}

void LEDController::setMode(int mode) {
    mode_ = mode;
    ws2812fx.setMode(mode_);
}

void LEDController::stop() {
    ws2812fx.stop();
}

void LEDController::service() {
    if(isAnimrunning){
      if(millis() - animStarttime < animRunDuration_){
        ws2812fx.service();  
      }else{
        ws2812fx.stop();
        isAnimrunning = false;
      }
    }
  }