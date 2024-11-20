#include "LEDController.h"
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

#define LED_COUNT 70

#define RXPINTOSOUNDMASTER 8 //connect  the Sound Sending TXPIN
#define TXPINTOSOUNDMASTER 9 //connect the Sound transmitting RXPIN


SoftwareSerial switchNumberReceiver(RXPINTOSOUNDMASTER, TXPINTOSOUNDMASTER); // RX, TX




                                                                                //brightness, speed, duration in millis 
mainLedController mainLedController(LED_COUNT, MAINLEDSTRIPEPIN, FX_MODE_RAINBOW_CYCLE,   100,        200,   5000); // Adjust parameters as needed

//int switchnumber;
volatile boolean balrogClosed = false;
volatile boolean balrogOpen = false;

void setup() {

  ardSerialInitPatch();

    #ifdef DEBUG
        Serial.begin(9600);
    #endif
    switchNumberReceiver.begin(TRXBAUDRATE);
    mainLedController.init();
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
                mainLedController.setMode(FX_MODE_RAINBOW_CYCLE);
                mainLedController.start();                  
              }else{
                DEBUG_PRINTLN("Start LED ANIM: FX_MODE_CHASE_FLASH ");
                mainLedController.setMode(FX_MODE_CHASE_FLASH);
                mainLedController.start();
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
    mainLedController.service();
}        

//Hack for arduion uno r4 - not used at the moment, instead
//If upload to Arduino UNO R4 does not work Click reset button twice for DFU mode
//Upload existing Blink script
void ardSerialInitPatch( void )
{ 
    static boolean do_once = true;
    if( do_once ){
        do_once = false;
        uint32_t start_time = millis();
        //Setup the baud rate
        Serial.begin( 115200 );
        while( !Serial && (millis() - start_time) < 5000 )
        {
            ; // wait for serial port to connect. Needed for native USB
        }
        Serial.println(F("!"));
    }
}
