/*
	Version 0.5 of Switch dedection
	Switch dedection is now working
	
	TODO exact debounding time to ensure a switch state change is only triggered once. 
	To be finalized when sound and led effects are integrated as well to check the timing
*/
#include <SoftwareSerial.h>

#define RXPIN 0 //connect SwitchstateDedector Receiving D0 to Switch Transmitter D1
#define TXPIN 6 //connect the SwitchstateDedector Transmitting D6 to the Hardware Receiving D0 of the Swtich Receiver EffectsSlave
#define TRXBAUDRATE 38400

#define BALROGHIT 1
#define LEFTRAMPMADE 2
#define RIGHTRAMPENTER 3
#define BALROGOPEN 4
#define BALROGCLOSED 5
#define LEFTORBITLOW 6



//variable declaration
int MatrixColumnP5Pin = 12;
int MatrixColumnP6Pin = 13;
int BalrogHitP6 = A0;  
volatile boolean balrogHit = false;
int LeftRampMadeP1 = A1; 
volatile boolean leftRampMade = false; 
int RightRampEnterP9 = A2;
volatile boolean RightRampEnter = false;
int LeftOrbitLowP5 = A5; 
volatile boolean LeftOrbitLow = false;
int balrogOpenP2 = A3; 
volatile boolean balrogOpen = false;
int balrogClosedP1 = A4; 
volatile boolean balrogClosed = false;
volatile int consecutiveBalrogHigh = 0;
int analogReadSwitchClosed = 300;
boolean balrogclosedReported = false;

SoftwareSerial switchSender(RXPIN, TXPIN); // RX, TX


// Arduino initialisieren
void setup() {
  switchSender.begin(TRXBAUDRATE);
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
}

void loop() {

// Warte auf Balrog Hit
  if(balrogHit){
    Serial.println("Balrog Hit");
    balrogHit = false;
    switchSender.write(BALROGHIT);
  }
  if(leftRampMade){
    balrogclosedReported=false;
    switchSender.write(LEFTRAMPMADE);
    //todo move to EffectsSlave
    if(balrogClosed){
        Serial.println("Playing YShallNP.mp3");
    }
  }
  if(RightRampEnter){
    RightRampEnter = false;
    switchSender.write(RIGHTRAMPENTER);
  }
  if(LeftOrbitLow){
    LeftOrbitLow = false;
    switchSender.write(LEFTORBITLOW);
  }

  //Balrog is blocking center Ramp
  //!leftRampMade: Hack for reasons not known LeftRampMade triggered wrong balrogclosed
  if(balrogClosed && !leftRampMade){
    switchSender.write(BALROGCLOSED);
  }
  //balrog open: Balrog is in not-active position not blocking center ramp
  //!leftRampMade: Hack for reasons not known LeftRampMade triggered wrong balrogclosed
  if(balrogOpen && balrogclosedReported && !leftRampMade){
    balrogclosedReported = false; 
    switchSender.write(BALROGOPEN);
  }
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