
int MatrixColumnP5Pin = 20;
int MatrixColumnP6Pin = 21;
int BalrogHitP6 = A8;  
volatile boolean balrogHit = false;
int LeftRampMadeP1 = A9; 
volatile boolean leftRampMade = false;
int RightRampEnterP9 = A10;
volatile boolean RightRampEnter = false;
int LeftOrbitLowP5 = A13; 
volatile boolean LeftOrbitLow = false;
int balrogOpenP2 = A11; 
volatile boolean balrogOpen = false;
int balrogClosedP1 = A12; 
volatile boolean balrogClosed = false;
volatile int consecutiveBalrogHigh = 0;
int analogReadSwitchClosed = 300;
boolean balrogclosedReported = false;




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
  if(balrogClosed && !leftRampMade){
    Serial.println("BalrogClosed");  
  }
  //balrog open: Balrog is in not-active position not blocking center ramp
  if(balrogOpen && balrogclosedReported && !leftRampMade){
    Serial.println("BalrogOpen"); 
    balrogclosedReported = false; 
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





