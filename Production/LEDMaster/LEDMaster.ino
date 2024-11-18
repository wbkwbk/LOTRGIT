#include "WS2812Wrapper.h"
#include <SoftwareSerial.h>

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

#define TRXBAUDRATE 38400

#define BALROGHIT 1
#define LEFTRAMPMADE 2
#define RIGHTRAMPENTER 3
#define BALROGOPEN 4
#define BALROGCLOSED 5
#define LEFTORBITLOW 6
#define MAINLEDSTRIPEPIN 7

#define RXPIN 8 //connect  the Switch Sending TXPIN
#define TXPIN 9 //connect the Switch transmitting RXPIN
SoftwareSerial switchNumberReceiver(RXPIN, TXPIN); // RX, TX

WS2812Wrapper mainLEDStripe(50,MAINLEDSTRIPEPIN, NEO_GRBW + NEO_KHZ800, 5000, 200, 200);

int switchnumber;
volatile boolean balrogClosed = false;
volatile boolean balrogOpen = false;

void setup() {

    #ifdef DEBUG
        Serial.begin(9600);
    #endif
    switchNumberReceiver.begin(TRXBAUDRATE);

}


void loop() {

    // Check for incoming serial data
    if (switchNumberReceiver.available() > 0) {
        int switchnumber = switchNumberReceiver.read();
        switch(switchnumber){
          case BALROGHIT:
            DEBUG_PRINTLN("EffectController::Balrog Hit");
          break;
          case LEFTRAMPMADE:
              DEBUG_PRINTLN("EffectController::Left Ramp Made");
              if(balrogOpen){
                DEBUG_PRINTLN("Start LED ANIM: FX_MODE_RAINBOW_CYCLE ");
                mainLEDStripe.startAnim(FX_MODE_RAINBOW_CYCLE);                  
              }else{
                mainLEDStripe.startAnim(FX_MODE_CHASE_FLASH);
                DEBUG_PRINTLN("Start LED ANIM: FX_MODE_CHASE_FLASH ");
              }
          break;
          case RIGHTRAMPENTER:
            DEBUG_PRINTLN("EffectController::Right Ramp Entered");  
          break;
          case BALROGOPEN:
            DEBUG_PRINTLN("EffectController::Balrog Open");  
            balrogClosed = false;
            balrogOpen = true;
          break;
          case BALROGCLOSED:
            DEBUG_PRINTLN("EffectController::Balrog Closed");  
            balrogClosed = true;
            balrogOpen = false;
          break;
          case LEFTORBITLOW:
            DEBUG_PRINTLN("EffectController::Left Orbit Low");
          break;          
        }  
    }
    mainLEDStripe.check();
}        
