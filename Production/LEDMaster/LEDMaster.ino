#include "LEDController.h"
#include <SoftwareSerial.h>
#include "GandalfMagicWand.h"

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

#define GANDALFWANDPINPIN 5
#define GANDALFFLASHINGDURATION 5000

#define LED_COUNT_SCHWERT 110
#define LED_COUNT_KAMM 100
#define LED_COUNT_MAIN 70

#define LED_SCHWERT 7
#define LED_KAMM 8
#define LED_MAIN 9
#define LEDANIMBRIGHTNESSMAIN 200
#define LEDANIMBRIGHTNESKAMMUNDSCHWERT 200
#define LEDANIMSPEED 200
#define LEDANIMDURATION 5000

// LEDController Instanzen
//                                ledCount,   ledPin, animMode, brightness, speed, animRunDuration);
LEDController ledControllerSchwert(LED_COUNT_SCHWERT, LED_SCHWERT, FX_MODE_RAINBOW_CYCLE,   LEDANIMBRIGHTNESKAMMUNDSCHWERT,        LEDANIMSPEED,   LEDANIMDURATION);
LEDController ledControllerKamm(LED_COUNT_KAMM, LED_KAMM, FX_MODE_RUNNING_LIGHTS,   LEDANIMBRIGHTNESKAMMUNDSCHWERT,        LEDANIMSPEED,   LEDANIMDURATION);
LEDController ledControllerMain(LED_COUNT_MAIN, LED_MAIN, FX_MODE_RUNNING_COLOR,   LEDANIMBRIGHTNESSMAIN,        LEDANIMSPEED,   LEDANIMDURATION);

//Communication
#define RXPINTOSOUNDMASTER 8 //connect  the Sound Sending TXPIN
#define TXPINTOSOUNDMASTER 9 //connect the Sound transmitting RXPIN


SoftwareSerial switchNumberReceiver(RXPINTOSOUNDMASTER, TXPINTOSOUNDMASTER); // RX, TX



GandalfMagicWand gandalfwand(GANDALFWANDPINPIN);

//int switchnumber;
volatile boolean balrogClosed = false;
volatile boolean balrogOpen = false;

void setup() {

  ardSerialInitPatch();

    #ifdef DEBUG
        Serial.begin(9600);
    #endif
    switchNumberReceiver.begin(TRXBAUDRATE);
    ledControllerSchwert.init();
    ledControllerKamm.init();
    ledControllerMain.init();
}


void loop() {
    // Check for incoming serial data
    if (switchNumberReceiver.available() > 0) {
        int switchnumber = switchNumberReceiver.read();
        switch(switchnumber){
          case BALROGHIT:
            DEBUG_PRINTLN("EffectController::Balrog Hit");
            gandalfwand.start(GANDALFFLASHINGDURATION);
            ledControllerSchwert.setMode(ledControllerSchwert.getBalrogHitEffect());
            ledControllerSchwert.setMode(ledControllerKamm.getBalrogHitEffect());
            ledControllerSchwert.setMode(ledControllerMain.getBalrogHitEffect());             

          break;
          case LEFTRAMPMADE:
              DEBUG_PRINTLN("EffectController::Left Ramp Made");
              if(balrogOpen){
                ledControllerSchwert.setMode(ledControllerSchwert.getBalrogOpenRampsEffect());
                ledControllerSchwert.setMode(ledControllerKamm.getBalrogOpenRampsEffect());
                ledControllerSchwert.setMode(ledControllerMain.getBalrogOpenRampsEffect());   
              }else{
                ledControllerSchwert.setMode(ledControllerSchwert.getBalrogClosedRampsEffect());
                ledControllerSchwert.setMode(ledControllerKamm.getBalrogClosedRampsEffect());
                ledControllerSchwert.setMode(ledControllerMain.getBalrogClosedRampsEffect());   
              }
              gandalfwand.start(GANDALFFLASHINGDURATION);
          break;
          case RIGHTRAMPENTER:
            DEBUG_PRINTLN("EffectController::Right Ramp Entered");  
              if(balrogOpen){
                ledControllerSchwert.setMode(ledControllerSchwert.getBalrogOpenRampsEffect());
                ledControllerSchwert.setMode(ledControllerKamm.getBalrogOpenRampsEffect());
                ledControllerSchwert.setMode(ledControllerMain.getBalrogOpenRampsEffect());   
              }else{
                ledControllerSchwert.setMode(ledControllerSchwert.getBalrogClosedRampsEffect());
                ledControllerSchwert.setMode(ledControllerKamm.getBalrogClosedRampsEffect());
                ledControllerSchwert.setMode(ledControllerMain.getBalrogClosedRampsEffect());   
              }
              gandalfwand.start(GANDALFFLASHINGDURATION);            
          break;
          case BALROGOPEN:
            DEBUG_PRINTLN("EffectController::Balrog Open");               
            balrogClosed = false;
            balrogOpen = true;
            ledControllerSchwert.setBalrogOpenState(balrogOpen);
            ledControllerKamm.setBalrogOpenState(balrogOpen);
            ledControllerMain.setBalrogOpenState(balrogOpen);
            gandalfwand.setBalrogOpenState(balrogOpen);
          break;
          case BALROGCLOSED:
            DEBUG_PRINTLN("EffectController::Balrog Closed");                         
            balrogClosed = true;
            balrogOpen = false;
            ledControllerSchwert.setBalrogOpenState(balrogOpen);
            ledControllerKamm.setBalrogOpenState(balrogOpen);
            ledControllerMain.setBalrogOpenState(balrogOpen);
            gandalfwand.setBalrogOpenState(balrogOpen);
            ledControllerSchwert.setMode(ledControllerSchwert.getBalrogClosedEffect());
            ledControllerSchwert.setMode(ledControllerKamm.getBalrogClosedEffect());
            ledControllerSchwert.setMode(ledControllerMain.getBalrogClosedEffect());             
          break;
          case LEFTORBITLOW:
            DEBUG_PRINTLN("EffectController::Left Orbit Low");            
              if(balrogOpen){
                ledControllerSchwert.setMode(ledControllerSchwert.getBalrogOpenLeftOrbitEffect());
                ledControllerSchwert.setMode(ledControllerKamm.getBalrogOpenLeftOrbitEffect());
                ledControllerSchwert.setMode(ledControllerMain.getBalrogOpenLeftOrbitEffect());   
              }else{
                ledControllerSchwert.setMode(ledControllerSchwert.getBalrogClosedLeftOrbitEffect());
                ledControllerSchwert.setMode(ledControllerKamm.getBalrogClosedLeftOrbitEffect());
                ledControllerSchwert.setMode(ledControllerMain.getBalrogClosedLeftOrbitEffect());   
              }           
          break;          
        }  
    }
    ledControllerSchwert.service();
    ledControllerKamm.service();
    ledControllerMain.service();
    gandalfwand.update();
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
