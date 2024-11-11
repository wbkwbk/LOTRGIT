#include "WS2812Wrapper.h"



	WS2812Wrapper::WS2812Wrapper(uint16_t num_leds, uint8_t pin, neoPixelType type, long runDuration, int brightness, int speed): ws2812fxInstance (num_leds, pin, type){
      animRunDuration = runDuration; 
      ws2812fxInstance.init();
      ws2812fxInstance.setBrightness(brightness);  //wertebereich von 0-255
     // Set the animation speed. 10=very fast, 5000=very slow
      ws2812fxInstance.setSpeed(speed);
      ws2812fxInstance.setMode(FX_MODE_COLOR_WIPE);  
	}

  void WS2812Wrapper::setAnimduration(long runDuration){
    animRunDuration = runDuration;  
  }

  void WS2812Wrapper::startAnim(int type){
    ws2812fxInstance.setMode(type);
    animStarttime = millis();
    ws2812fxInstance.start();
    isAnimrunning = true;
  }

  void WS2812Wrapper::check(){
    if(isAnimrunning){
      if(millis() - animStarttime < animRunDuration){
        ws2812fxInstance.service();  
      }else{
        ws2812fxInstance.stop();
        isAnimrunning = false;
      }
    }
  }
