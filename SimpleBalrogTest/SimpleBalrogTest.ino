

int MatrixColumn4Pin = 2;
int MatrixRow4Pin = A0;
volatile int consecutiveBalrogHigh = 0;
volatile boolean balorghit = false;

// Arduino initialisieren
void setup() {
  pinMode(MatrixColumn4Pin, INPUT);
  pinMode(MatrixRow4Pin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(MatrixColumn4Pin), InterruptRoutine, FALLING);
}

void loop() {

// Warte auf Balrog Hit
  if(balorghit){
    //Serial.println("Balrog Hit");
    balorghit = false;
  }

}


// Interrupt Routine. Wird aufgerufen bei fallender Flanke an MatrixColumn4Pin. Setzt Variable BalrogHit auf true, wenn MatrixRow4Pin HIGH.
void InterruptRoutine(){

// Hier evt. Verzögerung einbauen !
  delayMicroseconds(4);
  Serial.println("Interrupt");

  int MatrixRow4Status = digitalRead(MatrixRow4Pin);
  Serial.println(MatrixRow4Status);
  if(MatrixRow4Status == HIGH){
    consecutiveBalrogHigh++;
    //Serial.println("Balrog High");
    if(consecutiveBalrogHigh > 5){
        balorghit = true;
    }  
  }else{
    consecutiveBalrogHigh = 0;  
  }
}