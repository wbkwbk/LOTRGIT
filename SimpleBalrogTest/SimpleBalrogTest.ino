
int MatrixColumnP5Pin = 20;
int MatrixColumnP6Pin = 21;
int BalrogHitP6 = 22;  
volatile boolean balrogHit = false;
int LeftRampMadeP1 = 24; 
volatile boolean leftRampMade = false;
int RightRampEnterP9 = 26;
volatile boolean RightRampEnter = false;
int LeftOrbitLowP5 = 32; 
volatile boolean LeftOrbitLow = false;
int balrogOpenP2 = 28; 
volatile boolean balrogOpen = false;
volatile boolean balrogOpenReported = false;
int balrogClosedP1 = 30; 
volatile boolean balrogClosed = false;
volatile boolean balrogClosedReported = false;
volatile int consecutiveBalrogHigh = 0;



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
    leftRampMade = false;
  }
  if(RightRampEnter){
    Serial.println("Right Ramp Enter");
    RightRampEnter = false;
  }
  if(LeftOrbitLow){
    Serial.println("Left Orbit Low");
    LeftOrbitLow = false;
  }
  if(balrogOpen && !balrogOpenReported){
    Serial.println("BalrogOpen");
    balrogOpen = false;
    balrogOpenReported = true;
  }

  if(balrogClosed && !balrogClosedReported){
    Serial.println("BalrogClosed");
    balrogClosed = false;
    balrogClosedReported = true;
  }
}


// Interrupt Routine. Wird aufgerufen bei fallender Flanke an MatrixColumnP5Pin. Setzt Variable BalrogHit auf true, wenn BalrogHitPinP6 HIGH.
void P5_InterruptRoutine(){

  int BalrogHitStatus = digitalRead(BalrogHitP6);
  if(BalrogHitStatus == HIGH){
    consecutiveBalrogHigh++;
    //debounce
    if(consecutiveBalrogHigh > 20){
        balrogHit = true;
    }  
  }else{
    consecutiveBalrogHigh = 0;  
  }

  int RightRampEnterStatus = digitalRead(RightRampEnterP9);
  if(RightRampEnterStatus == HIGH){
    RightRampEnter = true;  
  }

  int balrogOpenStatus = digitalRead(balrogOpenP2);
  if(balrogOpenStatus == HIGH){
    balrogOpen = true;  
    balrogClosedReported = false;
  }else{
    balrogOpen = false;
  }

  int balrogClosedStatus = digitalRead(balrogClosedP1);
  if(balrogClosedStatus == HIGH){
    balrogClosed = true; 
    balrogOpenReported = false; 
  }else{
    balrogClosed = false;
  }


}

void P6_InterruptRoutine(){
  int LeftRampMadeStatus = digitalRead(LeftRampMadeP1);
  if(LeftRampMadeStatus == HIGH){
      leftRampMade = true;
  } 

  int LeftOrbitLowStatus = digitalRead(LeftOrbitLowP5);
  if(LeftOrbitLowStatus == HIGH){
    LeftOrbitLow = true;
  }
}





