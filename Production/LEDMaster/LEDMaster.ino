#include "LEDController.h"
#include <SoftwareSerial.h>



//#define DEBUG 1

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTDEC(x) Serial.print(x, DEC)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#endif

// Array of possible values
int values[] = {5000, 6000, 7000, 8000, 9000, 10000};

// Get the size of the array
const int arraySize = sizeof(values) / sizeof(values[0]);

// Array to track used values
bool used[arraySize] = {false};
int usedCount = 0;


#define TRXBAUDRATE 38400

#define BALROGHIT 1
#define LEFTRAMPMADE 2
#define RIGHTRAMPENTER 3
#define BALROGOPEN 4
#define BALROGCLOSED 5
#define LEFTORBITLOW 6

#define GANDALFFLASHINGDURATION 5000

#define LED_COUNT_SCHWERT 65
#define LED_COUNT_KAMM 63
#define LED_COUNT_MAIN 70
#define LED_COUNT_GANDALF_MAGIC_WAND 50

#define LED_SCHWERT 6
#define LED_KAMM 7
#define LED_MAIN 4
#define LED_MAGIC_WAND 5
#define LEDANIMBRIGHTNESSMAIN 200
#define LEDANIMBRIGHTNESKAMMUNDSCHWERT 200
#define LEDANIMSPEED 200
#define LEDANIMDURATION 5000

// LEDController Instanzen
//                                ledCount,   ledPin, animMode, brightness, speed, animRunDuration);
LEDController ledControllerSchwert(LED_COUNT_SCHWERT, LED_SCHWERT, FX_MODE_RAINBOW_CYCLE,   LEDANIMBRIGHTNESKAMMUNDSCHWERT,        LEDANIMSPEED,   LEDANIMDURATION);
LEDController ledControllerKamm(LED_COUNT_KAMM, LED_KAMM, FX_MODE_RUNNING_LIGHTS,   LEDANIMBRIGHTNESKAMMUNDSCHWERT,        LEDANIMSPEED,   LEDANIMDURATION);
LEDController ledControllerMain(LED_COUNT_MAIN, LED_MAIN, FX_MODE_RUNNING_COLOR,   LEDANIMBRIGHTNESSMAIN,        LEDANIMSPEED,   LEDANIMDURATION);
LEDController ledControllerGandalfMagicWand(LED_COUNT_GANDALF_MAGIC_WAND, LED_MAGIC_WAND, FX_MODE_RUNNING_COLOR,   LEDANIMBRIGHTNESSMAIN,        LEDANIMSPEED,   LEDANIMDURATION);


//Communication
#define RXPINTOSOUNDMASTER 8 //connect  the Sound Sending TXPIN
#define TXPINTOSOUNDMASTER 9 //connect the Sound transmitting RXPIN


SoftwareSerial switchNumberReceiver(RXPINTOSOUNDMASTER, TXPINTOSOUNDMASTER); // RX, TX



//int switchnumber;
volatile boolean balrogClosed = false;
volatile boolean balrogOpen = false;

void setup() {
  // Seed the random number generator with an analog pin
  randomSeed(analogRead(A0));
  ardSerialInitPatch();

    #ifdef DEBUG
        Serial.begin(9600);
    #endif

    ledControllerSchwert.init();
    ledControllerKamm.init();
    ledControllerMain.init();
    ledControllerGandalfMagicWand.init();
}


void loop() {
    // Check for incoming serial data
    if (switchNumberReceiver.available() > 0) {
        int animduration = getAnimduration();
        int switchnumber = switchNumberReceiver.read();
        switch(switchnumber){
          case BALROGHIT:
            DEBUG_PRINTLN("EffectController::Balrog Hit");
            ledControllerGandalfMagicWand.setMode(ledControllerGandalfMagicWand.getGandalfBalrogHitEffect(),animduration);
            setNextLEDMode(ledControllerSchwert.getBalrogHitEffect(), animduration);

          break;
          case LEFTRAMPMADE:
              DEBUG_PRINTLN("EffectController::Left Ramp Made");
              if(balrogOpen){
                setNextLEDMode(ledControllerSchwert.getBalrogOpenRampsEffect(), animduration);
              }else{
                setNextLEDMode(ledControllerSchwert.getBalrogClosedRampsEffect(), animduration);
              }
            ledControllerGandalfMagicWand.setMode(ledControllerGandalfMagicWand.getGandalfRampsEffect(),animduration);
          break;
          
          case RIGHTRAMPENTER:
            DEBUG_PRINTLN("EffectController::Right Ramp Entered");  
              if(balrogOpen){
                setNextLEDMode(ledControllerSchwert.getBalrogOpenRampsEffect(), animduration);
              }else{
                setNextLEDMode(ledControllerSchwert.getBalrogClosedRampsEffect(), animduration);                
              }
            ledControllerGandalfMagicWand.setMode(ledControllerGandalfMagicWand.getGandalfRampsEffect(),animduration);
          break;
          
          case BALROGOPEN:
            DEBUG_PRINTLN("EffectController::Balrog Open");               
            balrogClosed = false;
            balrogOpen = true;
            setBalrogState(balrogOpen);
            //added December 18
            ledControllerGandalfMagicWand.setMode(ledControllerGandalfMagicWand.getBalrogOpenRampsEffect(),animduration);
            setNextLEDMode(ledControllerSchwert.getBalrogOpenRampsEffect(), animduration);            
          break;
          
          case BALROGCLOSED:
            DEBUG_PRINTLN("EffectController::Balrog Closed");                         
            balrogClosed = true;
            balrogOpen = false;
            setBalrogState(balrogOpen);
            ledControllerGandalfMagicWand.setMode(ledControllerGandalfMagicWand.getBalrogClosedEffect(),animduration);
            setNextLEDMode(ledControllerSchwert.getBalrogClosedEffect(), animduration);             
          break;
          
          case LEFTORBITLOW:
            DEBUG_PRINTLN("EffectController::Left Orbit Low");            
              if(balrogOpen){
                setNextLEDMode(ledControllerSchwert.getBalrogOpenLeftOrbitEffect(), animduration);               
              }else{
                setNextLEDMode(ledControllerSchwert.getBalrogClosedLeftOrbitEffect(), animduration);  
              }                        
              ledControllerGandalfMagicWand.setMode(ledControllerGandalfMagicWand.getGandalfLeftOrbitEffect(),animduration);               
          break;          
        }  
    }
    ledControllerSchwert.service();
    ledControllerKamm.service();
    ledControllerMain.service();
    ledControllerGandalfMagicWand.service();
}        

void setBalrogState(int balrogstate){
  ledControllerSchwert.setBalrogOpenState(balrogstate);
  ledControllerKamm.setBalrogOpenState(balrogstate);
  ledControllerMain.setBalrogOpenState(balrogstate);
  ledControllerGandalfMagicWand.setBalrogOpenState(balrogstate);
}

void setNextLEDMode(int nextLEDEffect, int animDuration){
  ledControllerSchwert.setMode(nextLEDEffect,animDuration);
  ledControllerKamm.setMode(nextLEDEffect,animDuration);
  ledControllerMain.setMode(nextLEDEffect,animDuration);    
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
        switchNumberReceiver.begin( TRXBAUDRATE );
        while( !Serial && (millis() - start_time) < 5000 )
        {
            ; // wait for serial port to connect. Needed for native USB
        }
        DEBUG_PRINTLN("switchNumberReceiver::Initialized");
    }
}

int getAnimduration() {
  // If all values are used, reset the tracking array
  if (usedCount >= arraySize) {
    for (int i = 0; i < arraySize; i++) {
      used[i] = false;
    }
    usedCount = 0;
    
  }

  int randomIndex;

  // Find an unused value
  do {
    randomIndex = random(0, arraySize);
  } while (used[randomIndex]);

  // Mark the value as used
  used[randomIndex] = true;
  usedCount++;

  // Return the value at the random index
  return values[randomIndex];
}
