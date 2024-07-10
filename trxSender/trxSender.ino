#include <SoftwareSerial.h>   //We are using software serial so as not to conflict with serial download and monitor

#define RXReceivePin 8
#define TXSendPin 9


 #ifdef DEBUG
  #define DEBUG_PRINT(x)     Serial.print (x)
  #define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x) 
#endif

SoftwareSerial serialComm(RXReceivePin,TXSendPin); // RX, TX

int testvalue = 200;

void setup() {

  serialComm.begin(9600);
}

void loop()  {

 serialComm.println(200);
 waitFor(10000);
 serialComm.println(400);
 waitFor(10000);
}


 void waitFor(unsigned long milliseconds) {
  unsigned long start = millis(); // Startzeitpunkt speichern
  
  // Solange die vergangene Zeit kleiner ist als die gewünschte Wartezeit
  while (millis() - start < milliseconds) {
		
  }
 }