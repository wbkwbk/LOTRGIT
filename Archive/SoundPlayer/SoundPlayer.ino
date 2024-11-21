/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

/*
Fire LED Animation https://github.com/Electriangle/Fire_Main
*/

#define WS2812FXLEDANIM 0

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <SoftwareSerial.h>
#if WS2812FXLEDANIM == 1
    #include <WS2812FX.h>
#else
    #include "FastLED.h"
#endif

#define LED_COUNT 15
#define LED_PIN 22

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


#define EVENTBALLORGHIT 100
#define EVENTRIGHTRAMPENTER 200
#define EVENTLEFTRAMPMADE 300
#define EVENTLEFTORBITLOW 400
#define EVENTBALLORGOPEN 500
#define EVENTBALLOROGCLOSED 600

int BALLROGHITSTATUSARRAYPOS = 0;
int LEFTRAMPMADESTATUSARRAYPOS = 1;
int RIGHTRAMPENTERSTATUSARRAYPOS = 2;
int BALLORGOPENSTATUSARRAYPOS = 3;
int BALLORCLOSEDSTATUSARRAYPOS = 4;
int LEFTORBITLOWSTATUSARRAYPOS = 5;

boolean balrogopen = false;
volatile int consecutiveBalrogHigh = 0;
volatile boolean balorghit = false;

//timer function
// Define the interval (in milliseconds)
const unsigned long InterruptIntervall1 = 5000;  // 5 seconds
const unsigned long InterruptIntervall2 = 2;  // 5 seconds

// Variable to store the last time the routine was called
unsigned long previousMillisI1 = 0;
unsigned long previousMillisI2 = 0;

#define RXReceivePin 8
#define TXSendPin 9

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

unsigned long lastTimeSwitchActived[6]={-1,-1,-1,-1,-1,-1,};
int BUTTONDEBOUNCETIME = 200;

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  //Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  
SoftwareSerial serialComm(RXReceivePin, TXSendPin);
#if WS2812FXLEDANIM == 1
    WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#else
    CRGB leds[LED_COUNT];
#endif


void setup() {
  serialComm.begin(115200);
  Serial.begin(9600);
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
  printDirectory(SD.open("/"), 0);
  
  // Set volume for left, right channels. lower numbers == louder volume!
  // accepts values between 0 and 255 for left and right.
  musicPlayer.setVolume(1,1);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    Serial.println(F("DREQ pin is not an interrupt pin"));
  // Play one file, don't return until complete
  //Serial.println(F("YShallNP"));
  //musicPlayer.playFullFile("/YShallNP.mp3");
  //Serial.println(F("CobRoar1"));
  //musicPlayer.playFullFile("/CobRoar1.mp3");
  // Play another file in the background, REQUIRES interrupts!
  //Serial.println(F("Playing track 002"));
  //musicPlayer.startPlayingFile("/track002.mp3");

#if WS2812FXLEDANIM == 1
    ws2812fx.init();
    ws2812fx.setBrightness(255);
    ws2812fx.setSpeed(200);
    ws2812fx.setMode(FX_MODE_CHASE_BLACKOUT_RAINBOW);
    ws2812fx.start();
#else
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);    // Set power limit of LED strip to 5V, 1500mA
    FastLED.clear();                                    // Initialize all LEDs to "OFF"
#endif

}

void loop() {
    unsigned long currentMillis = millis();
  // File is playing in the background

    if(!musicPlayer.playingMusic){
        musicPlayer.startPlayingFile("/YShallNP.mp3");
    }
    //while (musicPlayer.playingMusic) {
    //    
    //}
    #if WS2812FXLEDANIM == 1
        ws2812fx.service();
    #else
    if(balrogopen){
        Fire(1, 10, 100, 80, false);
    }else{
        FastLED.clear();
        FastLED.show();
    }
    #endif  


    // Check if intervall1 has passed
    if (currentMillis - previousMillisI1 >= InterruptIntervall1) {
    // Save the current time as the last time the routine was called
        previousMillisI1 = currentMillis;
    // Call the routine
        timedInterruptRoutine1();
    }

    // Check if intervall2 has passed
    if (currentMillis - previousMillisI2 >= InterruptIntervall2) {
    // Save the current time as the last time the routine was called
        previousMillisI2 = currentMillis;
    // Call the routine
        timedInterruptRoutine2();
    }

    if(serialComm.available() > 0){
        int command = serialComm.parseInt();
        switch(command){
            case EVENTBALLORGHIT:
            if(checkDebounceTimePassed(BALLROGHITSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received BallroghHit: "));
                Serial.println(command);
                musicPlayer.startPlayingFile("/CobRoar1.mp3");
            }
            break;

            case EVENTRIGHTRAMPENTER:
            if(checkDebounceTimePassed(RIGHTRAMPENTERSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received RightRampEnter: "));
                Serial.println(command);
                musicPlayer.startPlayingFile("/YShallNP.mp3");
            }
            break;    
            case EVENTLEFTRAMPMADE:
            if(checkDebounceTimePassed(LEFTRAMPMADESTATUSARRAYPOS, millis())){
                Serial.print(F("Command received LeftRampMade: "));
                Serial.println(command);
                musicPlayer.startPlayingFile("/YShallNP.mp3");
            }
            break;    
            case EVENTLEFTORBITLOW:
            if(checkDebounceTimePassed(LEFTORBITLOWSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received LeftorbitLow: "));
                Serial.println(command);
                musicPlayer.startPlayingFile("/YShallNP.mp3");
            }
            break;    
            case EVENTBALLORGOPEN:
            if(checkDebounceTimePassed(BALLORGOPENSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received BallrogOpen: "));
                Serial.println(command);
                musicPlayer.startPlayingFile("/YShallNP.mp3");
            }
            break;    
            case EVENTBALLOROGCLOSED:
            if(checkDebounceTimePassed(BALLORCLOSEDSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received BallrogClosed: "));
                Serial.println(command);
                musicPlayer.startPlayingFile("/YShallNP.mp3");
            }
            break;    
        }
    }


/*
    musicPlayer.playFullFile("/YSHALL~1.MP3");
    musicPlayer.playFullFile("/CobRoar1.mp3");
   
  if (musicPlayer.stopped()) {
    Serial.println("Done playing music");
    while (1) {
      delay(10);  // we're done! do nothing...
    }
  }
  if (Serial.available()) {
    char c = Serial.read();
    
    // if we get an 's' on the serial console, stop!
    if (c == 's') {
      musicPlayer.stopPlaying();
    }
    
    // if we get an 'p' on the serial console, pause/unpause!
    if (c == 'p') {
      if (! musicPlayer.paused()) {
        Serial.println("Paused");
        musicPlayer.pausePlaying(true);
      } else { 
        Serial.println("Resumed");
        musicPlayer.pausePlaying(false);
      }
    }
  }

  //delay(100);
*/
}

void timedInterruptRoutine1() {
  balrogopen = !balrogopen;
}

void timedInterruptRoutine2() {
    consecutiveBalrogHigh++;
    //Serial.println("Balrog High");
    if(consecutiveBalrogHigh > 5){
        balorghit = true;
    }else{
    consecutiveBalrogHigh = 0;  
  }  
}

boolean checkDebounceTimePassed(int currentSwitch, unsigned long currentTime){
    boolean timePassed=false;

    if(currentTime - lastTimeSwitchActived[currentSwitch] > BUTTONDEBOUNCETIME){
        lastTimeSwitchActived[currentSwitch] = currentTime;
        timePassed = true;   
    }
    return timePassed;
}

/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

