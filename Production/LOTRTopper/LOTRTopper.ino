/*
	Version 0.5 of Switch dedection
	Switch dedection is now working
	
	TODO exact debounding time to ensure a switch state change is only triggered once. 
	To be finalized when sound and led effects are integrated as well to check the timing
*/

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include "WS2812Wrapper.h"

//SoundShield
// define the pins used
#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
//define BREAKOUT_RESET  9      // VS1053 reset pin (output)
//define BREAKOUT_CS     10     // VS1053 chip select pin (output)
//define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin
//END Sound Shield

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  //Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

//variable declaration
int MatrixColumnP5Pin = 20; //Interrupt 1
int MatrixColumnP6Pin = 21; //Interrupt 0
int BalrogHitP6 = A8;  //Red Cable
volatile boolean balrogHit = false;
int LeftRampMadeP1 = A9; // Orange Cable
volatile boolean leftRampMade = false; 
int RightRampEnterP9 = A10; // Yellow Cable
volatile boolean RightRampEnter = false;
int LeftOrbitLowP5 = A13; //Purple cable
volatile boolean LeftOrbitLow = false;
int balrogOpenP2 = A11; //Green cable
volatile boolean balrogOpen = false;
int balrogClosedP1 = A12; //Blue cable
volatile boolean balrogClosed = false;
volatile int consecutiveBalrogHigh = 0;
int analogReadSwitchClosed = 300;
boolean balrogclosedReported = false;

//                          num_led, pin, neoPixelType, animduration, brightness, speed
WS2812Wrapper mainLEDStripe(5,10, NEO_GRBW + NEO_KHZ800, 5000, 200, 200);



// Arduino initialisieren
void setup() {
  pinMode(MatrixColumnP5Pin, INPUT);
  pinMode(MatrixColumnP6Pin, INPUT);
  pinMode(BalrogHitP6, INPUT);
  pinMode(LeftRampMadeP1, INPUT);
  pinMode(RightRampEnter, INPUT);
  pinMode(LeftOrbitLowP5, INPUT);
  pinMode(balrogOpenP2, INPUT);
  pinMode(balrogClosedP1, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(MatrixColumnP5Pin), P5_InterruptRoutine, FALLING);
  attachInterrupt(digitalPinToInterrupt(MatrixColumnP6Pin), P6_InterruptRoutine, FALLING);


  Serial.println("Adafruit VS1053 Simple Test");
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     //while (1);
  }
  Serial.println(F("VS1053 found"));
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    //while (1);  // don't do anything more
  }

  // list files
  //printDirectory(SD.open("/"), 0);
  
  // Set volume for left, right channels. lower numbers == louder volume!
  // accepts values between 0 and 255 for left and right.
  musicPlayer.setVolume(1,1);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    Serial.println(F("DREQ pin is not an interrupt pin"));

}

void loop() {

// Warte auf Balrog Hit
  if(balrogHit){
    Serial.println("Balrog Hit");
    balrogHit = false;
  }
  if(leftRampMade){
    Serial.println("Left Ramp Made");
    balrogclosedReported=false;
    if(balrogClosed){
        Serial.println("Playing YShallNP.mp3");
        if(!musicPlayer.playingMusic){
          musicPlayer.startPlayingFile("/YShallNP.mp3");
          Serial.println("Start LED ANIM: FX_MODE_RAINBOW_CYCLE ");
          mainLEDStripe.startAnim(FX_MODE_RAINBOW_CYCLE);
        }
    }else{
      mainLEDStripe.startAnim(FX_MODE_CHASE_FLASH);
      Serial.println("Start LED ANIM: FX_MODE_CHASE_FLASH ");
    }
  }
  if(RightRampEnter){
    Serial.println("Right Ramp Enter");
    RightRampEnter = false;
  }
  if(LeftOrbitLow){
    Serial.println("Left Orbit Low");
    LeftOrbitLow = false;
  }

  //Balrog is blocking center Ramp
  //!leftRampMade: Hack for reasons not known LeftRampMade triggered wrong balrogclosed
  if(balrogClosed && !leftRampMade){
    Serial.println("BalrogClosed");  
  }
  //balrog open: Balrog is in not-active position not blocking center ramp
  //!leftRampMade: Hack for reasons not known LeftRampMade triggered wrong balrogclosed
  if(balrogOpen && balrogclosedReported && !leftRampMade){
    Serial.println("BalrogOpen"); 
    balrogclosedReported = false; 
  }

  //now check all the ledstripes if a running anim has to stop
  mainLEDStripe.check();
}


// Interrupt Routine. Wird aufgerufen bei fallender Flanke an MatrixColumnP5Pin. Setzt Variable BalrogHit auf true, wenn BalrogHitPinP6 HIGH.
void P5_InterruptRoutine(){

  int BalrogHitStatus = analogRead(BalrogHitP6);
  if(BalrogHitStatus > analogReadSwitchClosed){
    consecutiveBalrogHigh++;
    //debounce
    if(consecutiveBalrogHigh > 20){
        balrogHit = true;
    }  
  }else{
    consecutiveBalrogHigh = 0;  
    balrogHit = false;
  }

  int RightRampEnterStatus = analogRead(RightRampEnterP9);
  if(RightRampEnterStatus < analogReadSwitchClosed){
    RightRampEnter = true;  
  }else{
    RightRampEnter = false; 
  }

  int balrogOpenStatus = analogRead(balrogOpenP2);
  if(balrogOpenStatus < analogReadSwitchClosed){
    balrogOpen = true; 
  }else{
    balrogOpen = false;
  }

  int balrogClosedStatus = analogRead(balrogClosedP1);
  if(balrogClosedStatus < analogReadSwitchClosed){
    balrogClosed = true; 
    balrogclosedReported = true;
  }else{
    balrogClosed = false;
  }

}

void P6_InterruptRoutine(){
  int LeftRampMadeStatus = analogRead(LeftRampMadeP1);
  if(LeftRampMadeStatus < analogReadSwitchClosed){
      leftRampMade = true;
      balrogclosedReported=false;
  }else{
      leftRampMade = false;
  } 

  int LeftOrbitLowStatus = analogRead(LeftOrbitLowP5);
  if(LeftOrbitLowStatus < analogReadSwitchClosed){
    LeftOrbitLow = true;
  }
  else{
    LeftOrbitLow = false;  
  }
}





