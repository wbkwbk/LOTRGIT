/*
	Version 0.5 of Switch dedection
	Switch dedection is now working
	
	TODO exact debounding time to ensure a switch state change is only triggered once. 
	To be finalized when sound and led effects are integrated as well to check the timing
*/
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

#define RXPINTOEFFECTSMASTER 10 //10 for MEGA connect to Effectscontroller RXPIN
#define TXPINTOEFFECTSMASTER 11 //11 for MEGA connect to Effects controller TXPIN
#define TRXBAUDRATE 38400

#define BALROGHIT 1
#define LEFTRAMPMADE 2
#define RIGHTRAMPENTER 3
#define BALROGOPEN 4
#define BALROGCLOSED 5
#define LEFTORBITLOW 6





//variable declaration
int MatrixColumnP5Pin = 2; //20;//2;
int MatrixColumnP6Pin = 3; //21; //3;
int BalrogHitP6 = A0; //A8; //A0;  
volatile boolean balrogHit = false;
int LeftRampMadeP1 = A1; //A9; //A1; 
volatile boolean leftRampMade = false; 
int RightRampEnterP9 = A2; //A10; //A2;
volatile boolean RightRampEnter = false;
int LeftOrbitLowP5 = A5; //A13; //A5; 
volatile boolean LeftOrbitLow = false;
int balrogOpenP2_31 = A3; //A11; //A3; 
volatile boolean balrogOpen = false;
int balrogClosedP1_32 = A4; //A12; //A4; 
volatile boolean balrogClosed = false;
volatile int consecutiveBalrogHigh = 0;
int analogReadSwitchClosed = 300;
//for reasons not known yet Balrogclosed is sometimes as high as 600
int analogReadSwitchClosedBalrogHit = 800;
boolean lastBalrogClosedValue;
boolean lastBalrogOpenvalue;

// Variable for last stable state and time
volatile unsigned long lastDebounceTimeBalrogHit = 0;
volatile unsigned long debounceDelayBalorgHit = 50;  // debounce time in millis
boolean lastBalrogHitState = false;
volatile unsigned long debounceDelayGeneralSwitch = 50;  // debounce time in millis
volatile unsigned long lastDebounceTimeLeftRampMade = 0;
boolean lastLeftRampMadeState = false;
volatile unsigned long lastDebounceTimeLeftOrbit = 0;
boolean lastLeftOrbitMadeState = false;
volatile unsigned long lastDebounceTimeRightRampEnter = 0;
boolean lastRightRampMadeState = false;

SoftwareSerial switchSender(RXPINTOEFFECTSMASTER, TXPINTOEFFECTSMASTER); // RX, TX

//                          num_led, pin, neoPixelType, animduration, brightness, speed


// Arduino initialisieren
void setup() {
  switchSender.begin(TRXBAUDRATE);
  pinMode(MatrixColumnP5Pin, INPUT);
  pinMode(MatrixColumnP6Pin, INPUT);
  pinMode(BalrogHitP6, INPUT);
  pinMode(LeftRampMadeP1, INPUT);
  pinMode(RightRampEnter, INPUT);
  pinMode(LeftOrbitLowP5, INPUT);
  pinMode(balrogOpenP2_31, INPUT);
  pinMode(balrogClosedP1_32, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(MatrixColumnP5Pin), P5_InterruptRoutine, FALLING);
  attachInterrupt(digitalPinToInterrupt(MatrixColumnP6Pin), P6_InterruptRoutine, FALLING);

   
}

void loop() {
  // Prüfe auf Balrog Hit
  if(balrogHit){
      balrogHit = false;
      switchSender.write(BALROGHIT);
      DEBUG_PRINTLN("SwitchSender::BALROGHIT");
  }

  if(leftRampMade){
    leftRampMade=false;
    switchSender.write(LEFTRAMPMADE);
    DEBUG_PRINTLN("SwitchSender::LEFTRAMPMADE"); 
    //todo move to EffectsSlave
    if(balrogOpen){
     //todo to be removed
    }else{
      //todo to be removed
    }
  }

  if(RightRampEnter){
    RightRampEnter = false;
    switchSender.write(RIGHTRAMPENTER);
    DEBUG_PRINTLN("SwitchSender::RIGHTRAMPENTER"); 
  }

  if(LeftOrbitLow){
    LeftOrbitLow = false;
    switchSender.write(LEFTORBITLOW);
    DEBUG_PRINTLN("SwitchSender::LEFTORBITLOW");
  }

  //Balrog is NOT blocking center Ramp
  if(balrogClosed){ 
    if(!lastBalrogClosedValue){
      switchSender.write(BALROGCLOSED);
      DEBUG_PRINTLN("SwitchSender::BALROGCLOSED"); 
      lastBalrogClosedValue = true;
    }
  }else{
    lastBalrogClosedValue = false;
  }

  //balrog open: Balrog is in active position blocking center ramp
  if(balrogOpen){ 
    if(!lastBalrogOpenvalue){
      switchSender.write(BALROGOPEN);
      DEBUG_PRINTLN("SwitchSender::BALROGOPEN");   
      lastBalrogOpenvalue = true;     
    }
  }else{
    lastBalrogOpenvalue = false;    
  }

}


// Interrupt Routine. Wird aufgerufen bei fallender Flanke an MatrixColumnP5Pin. Setzt Variable BalrogHit auf true, wenn BalrogHitPinP6 HIGH.
void P5_InterruptRoutine(){

  int balrogOpenStatus_31 = analogRead(balrogOpenP2_31);
  int balrogClosedStatus_32 = analogRead(balrogClosedP1_32);
  //Switchb 31: Balrogopen is open and Switch 32 Balrogclosed is closed then balrog is open
  if(balrogOpenStatus_31 > analogReadSwitchClosed){
    if(balrogClosedStatus_32 < analogReadSwitchClosed){
      balrogOpen = true;   
    }else{
      balrogOpen = false; 
    }
  }else{
    balrogOpen = false;  
  }

  //Switch 32 Balrogclosed is Open and Switch 31 Balrogopen is closed: Balrog is closed
  if(balrogClosedStatus_32 > analogReadSwitchClosed){
    if(balrogOpenStatus_31 < analogReadSwitchClosed){
      balrogClosed = true;
    }else{
      balrogClosed = false;    
    }
  }else{
    balrogClosed = false;  
  }
  

  int RightRampEnterStatus = analogRead(RightRampEnterP9);
  if(RightRampEnterStatus < analogReadSwitchClosed){
    if(!lastRightRampMadeState){
      // wait until value is stable
      if (millis() - lastDebounceTimeRightRampEnter > debounceDelayGeneralSwitch) {
        RightRampEnter = true;
        lastDebounceTimeRightRampEnter = millis();  // update last time
        lastRightRampMadeState = true;
      }
    }
    lastRightRampMadeState = true;
  } else {
    lastRightRampMadeState = false;
    RightRampEnter = false;  // Reset the Hit-Flag
  } 

  int BalrogHitStatus = analogRead(BalrogHitP6);
  if(BalrogHitStatus > analogReadSwitchClosedBalrogHit){
    if (!lastBalrogHitState) {
      // wait until value is stable
      if (millis() - lastDebounceTimeBalrogHit > debounceDelayBalorgHit) {
        balrogHit = true;
        lastDebounceTimeBalrogHit = millis();  // update last time
      }
    }
    lastBalrogHitState = true;
  } else {
    lastBalrogHitState = false;
    balrogHit = false;  // Reset the Hit-Flag
  }

}

void P6_InterruptRoutine(){
  int LeftRampMadeStatus = analogRead(LeftRampMadeP1);
  if(LeftRampMadeStatus < analogReadSwitchClosed){
    if(!lastLeftRampMadeState){
      // wait until value is stable
      if (millis() - lastDebounceTimeLeftRampMade > debounceDelayGeneralSwitch) {
        leftRampMade = true;
        lastLeftRampMadeState = true;
        lastDebounceTimeLeftRampMade = millis();  // update last time
      }      
    }
  }else{
      lastLeftRampMadeState = false;
      leftRampMade = false;
  } 

  int LeftOrbitLowStatus = analogRead(LeftOrbitLowP5);
  if(LeftOrbitLowStatus < analogReadSwitchClosed){
    if(!lastLeftOrbitMadeState){
      if(millis() - lastDebounceTimeLeftOrbit > debounceDelayGeneralSwitch) {
            LeftOrbitLow = true;
            lastLeftOrbitMadeState = true;
            lastDebounceTimeLeftOrbit = millis();
      }
    }
  }
  else{
    LeftOrbitLow = false;  
    lastLeftOrbitMadeState = false;
  }
}


int readStableValue(int pin) {
  long sum = 0;
  const int numReadings = 10; // Anzahl der Messungen
  for (int i = 0; i < numReadings; i++) {
    sum += analogRead(pin);
  }
  return sum / numReadings;
}