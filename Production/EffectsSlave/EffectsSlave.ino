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


#define BALROGHIT 1
#define LEFTRAMPMADE 2
#define RIGHTRAMPENTER 3
#define BALROGOPEN 4
#define BALROGCLOSED 5
#define LEFTORBITLOW 6

#define RXPIN 0 //connect  the Switch Receiving D0 to the SwitchstateDedector Sender D6
#define TXPIN 1 //connect the Switch transmitting D1 to the SwitchtstateDedector Receiver D0

#define TRXBAUDRATE 38400

int switchnumber;
volatile boolean balrogClosed = false;

SoftwareSerial switchNumberReceiver(RXPIN, TXPIN); // RX, TX

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
            DEBUG_PRINTLN("Balrog Hit");
          break;
          case LEFTRAMPMADE:
              if(balrogClosed){
                DEBUG_PRINTLN("Playing YShallNP.mp3");
              }
          case RIGHTRAMPENTER:
            DEBUG_PRINTLN("Right Ramp Entered");  
          case BALROGOPEN:
            DEBUG_PRINTLN("Balrog Open");  
            balrogClosed = false;
          case BALROGCLOSED:
            DEBUG_PRINTLN("Balrog Closed");  
            balrogClosed = true;
          case LEFTORBITLOW:
            DEBUG_PRINTLN("Left Orbit Low");          
        }  
    }
}        

