#include "WS2812Wrapper.h"


#define DEBUG 1

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTDEC(x) Serial.print(x, DEC)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#endif
#define MAINLEDSTRIPEPIN 7

int animMode = 1;

WS2812Wrapper mainLEDStripe(50,MAINLEDSTRIPEPIN, NEO_GRBW + NEO_KHZ800, 10000, 100, 10);

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    while(!Serial){};
  #endif
}

void loop() { 
  if(!mainLEDStripe.isAnimRunning()){
    mainLEDStripe.startAnim(animMode); 
    DEBUG_PRINTLN(animMode);
    delay(2000);
    animMode++;
    if(animMode == 56){
      animMode = 1;
    }
  }

  mainLEDStripe.check();
}        
