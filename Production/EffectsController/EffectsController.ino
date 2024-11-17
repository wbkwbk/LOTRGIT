#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

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


#define BALROGHIT 1
#define LEFTRAMPMADE 2
#define RIGHTRAMPENTER 3
#define BALROGOPEN 4
#define BALROGCLOSED 5
#define LEFTORBITLOW 6

#define RXPIN 51 //connect  the Switch Receiving D0 to the SwitchstateDedector Sender D6
#define TXPIN 53 //connect the Switch transmitting D1 to the SwitchtstateDedector Receiver D0

#define TRXBAUDRATE 38400

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

int switchnumber;
volatile boolean balrogClosed = false;

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  //Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

SoftwareSerial switchNumberReceiver(RXPIN, TXPIN); // RX, TX

void setup() {

    #ifdef DEBUG
        Serial.begin(9600);
    #endif
    switchNumberReceiver.begin(TRXBAUDRATE);
  if (! musicPlayer.begin()) { // initialise the music player
     DEBUG_PRINTLN("Couldn't find VS1053, do you have the right pins defined?");
     //while (1);
  }
  DEBUG_PRINTLN("VS1053 found");
  
   if (!SD.begin(CARDCS)) {
    DEBUG_PRINTLN("SD failed, or not present");
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
    DEBUG_PRINTLN("DREQ pin is not an interrupt pin");    
}

void loop() {

    // Check for incoming serial data
    if (switchNumberReceiver.available() > 0) {
        int switchnumber = switchNumberReceiver.read();
        DEBUG_PRINTLN(switchnumber);
        switch(switchnumber){
          case BALROGHIT:
            DEBUG_PRINTLN("EffectController::Balrog Hit");
          break;
          case LEFTRAMPMADE:
              DEBUG_PRINTLN("EffectController::Left Ramp Made");
              if(!balrogClosed){
                if(!musicPlayer.playingMusic){
                  musicPlayer.startPlayingFile("/YShallNP.mp3");
                }  
              }
          break;
          case RIGHTRAMPENTER:
            DEBUG_PRINTLN("EffectController::Right Ramp Entered");  
          break;
          case BALROGOPEN:
            DEBUG_PRINTLN("EffectController::Balrog Open");  
            balrogClosed = false;
          break;
          case BALROGCLOSED:
            DEBUG_PRINTLN("EffectController::Balrog Closed");  
            balrogClosed = true;
          break;
          case LEFTORBITLOW:
            DEBUG_PRINTLN("EffectController::Left Orbit Low");
          break;          
        }  
    }
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
