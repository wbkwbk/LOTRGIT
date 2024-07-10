#include "PinChangeInterrupt.h"


#define EVENTBALLORGHIT 100
#define EVENTRIGHTRAMPENTER 200
#define EVENTLEFTRAMPMADE 300
#define EVENTLEFTORBITLOW 400
#define EVENTBALLROGOPEN 500
#define EVENTBALLOROGCLOSED 600

 #define DEBUG 1

 #ifdef DEBUG
  #define DEBUG_PRINT(x)     Serial.print (x)
  #define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x) 
#endif
int WaitInMainLoop = 1000;
boolean BallRogOpen = false;

int SwitchState[6]={-1,-1,-1,-1,-1,-1};


char *Switchnames[] = { "BALLORGHIT", "LEFTRAMPMADE",  "RIGHTRAMPENTER",  "BALLORGOPEN",  "BALLOROGCLOSED",  "LEFTORBITLOWPIN"};
int BALLORGHITPIN = A0; //14 analog A0
int LEFTRAMPMADEPIN = A1; //14 analog A0
int RIGHTRAMPENTERPIN = A2;
int BALLORGOPENPIN = A3;
//When ballrog is active, bevore the middle ramp this switch is closed
int BALLOROGCLOSEDPIN = A4;
int LEFTORBITLOWPIN = A5;
int MATRIXCOLUMN_five_PIN = 2;
int MATRIXCOLUMN_six_PIN = 3;
int VOLTAGETHRESHOLD = 400;
int NUMBEROFSWITCHES = 6;
int BALLROGHITSTATUSARRAYPOS = 0;
int LEFTRAMPMADESTATUSARRAYPOS = 1;
int RIGHTRAMPENTERSTATUSARRAYPOS = 2;
int BALLORGOPENSTATUSARRAYPOS = 3;
int BALLORCLOSEDSTATUSARRAYPOS = 4;
int LEFTORBITLOWSTATUSARRAYPOS = 5;


//PostNeoSWSerial LEDserialComm(LEDRXReceivePin,LEDTXSendPin); // RX, TX


void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  //Ballrog is open when ballrog is hit, switch is usually closed
  pinMode(BALLORGHITPIN, INPUT); 
  pinMode(LEFTRAMPMADEPIN, INPUT);
  pinMode(RIGHTRAMPENTERPIN, INPUT);
  pinMode(BALLORGOPENPIN, INPUT);
  pinMode(BALLOROGCLOSEDPIN, INPUT);
  pinMode(LEFTORBITLOWPIN, INPUT);
  DEBUG_PRINTLN("starting");
  //enable serial communication to the LEDArduio to send according commands upon switches activated
  //LEDserialComm.begin(9600);

  // attach the new PinChangeInterrupts and enable event functions below

  attachPCINT(digitalPinToPCINT(RIGHTRAMPENTERPIN), rightRampEnter, CHANGE);
  attachPCINT(digitalPinToPCINT(BALLORGHITPIN), ballrogHit, FALLING);
  attachPCINT(digitalPinToPCINT(LEFTRAMPMADEPIN), leftRampMade, CHANGE);
  //attachPCINT(digitalPinToPCINT(BALLORGOPENPIN), ballrogOpen, CHANGE);
  //attachPCINT(digitalPinToPCINT(BALLOROGCLOSEDPIN), ballrogClosed, CHANGE);
  attachPCINT(digitalPinToPCINT(LEFTORBITLOWPIN), leftOrbitLow, CHANGE);
  
}

void ballrogHit(void) {
  int rowVal = analogRead(BALLORGHITPIN);
  int colVal = digitalRead(MATRIXCOLUMN_five_PIN);
    DEBUG_PRINT("BalrogAnalogValue: ");
    DEBUG_PRINT(rowVal);
        DEBUG_PRINT("  Column Value:");
    if(colVal == LOW ){
        DEBUG_PRINTLN("  LOW");    
    }else{
        DEBUG_PRINTLN("  HIGH");   
    }
}

void rightRampEnter(void) {
  checkifSwitchisActivated(RIGHTRAMPENTERPIN, MATRIXCOLUMN_five_PIN, EVENTRIGHTRAMPENTER, Switchnames[2]);
}

void leftRampMade(void) {
  checkifSwitchisActivated(LEFTRAMPMADEPIN, MATRIXCOLUMN_six_PIN, EVENTLEFTRAMPMADE, Switchnames[1]);
}

void ballrogOpen(void) {
  checkifSwitchisActivated(BALLORGOPENPIN, MATRIXCOLUMN_five_PIN, EVENTBALLROGOPEN, Switchnames[3]);
}

void ballrogClosed(void) {
  checkifSwitchisActivated(BALLOROGCLOSEDPIN, MATRIXCOLUMN_five_PIN, EVENTBALLOROGCLOSED, Switchnames[4]);
}

void leftOrbitLow(void) {
  checkifSwitchisActivated(LEFTORBITLOWPIN, MATRIXCOLUMN_six_PIN, EVENTLEFTORBITLOW, Switchnames[5]);
}

void checkifSwitchisActivated(int switchNumber, int columnNumber, int eventMessage, char* SwitchName){
      if(analogRead(switchNumber) < VOLTAGETHRESHOLD &&  digitalRead(columnNumber) == LOW){
        DEBUG_PRINT("Switch Activated: ");
        DEBUG_PRINTLN(SwitchName);
  }
}


void loop() {
    waitFor(WaitInMainLoop);
}

 void waitFor(unsigned long milliseconds) {
    unsigned long start = millis(); // Startzeitpunkt speichern
  // Solange die vergangene Zeit kleiner ist als die gewünschte Wartezeit
  //analogSwitchValue = analogRead(A2);
  //DEBUG_PRINT("RightRampMade AnalogValue: ");
  //DEBUG_PRINTLN(analogSwitchValue);

    while (millis() - start < milliseconds) {
       //     DEBUG_PRINT(millis());
       //     DEBUG_PRINTLN(":waitFor");    
    }
}


