#include <SoftwareSerial.h>   //We are using software serial so as not to conflict with serial download and monitor


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
int WaitInMainLoop = 1;

int SwitchState[6]={-1,-1,-1,-1,-1,-1};


char *Switchnames[] = { "BALLORGHIT", "LEFTRAMPMADE",  "RIGHTRAMPENTER",  "BALLORGOPEN",  "BALLOROGCLOSED",  "LEFTORBITLOWPIN"};
int BALLORGHITPIN = A0; //14 analog A0
int LEFTRAMPMADEPIN = A1; //14 analog A0
int RIGHTRAMPENTERPIN = A2;
int BALLORGOPENPIN = A3;
//When ballrog is active, bevore the middle ramp this switch is closed
int BALLOROGCLOSEDPIN = A4;
int LEFTORBITLOWPIN = A5;
int MATRIXCOLUMN5PIN = 2;
int MATRIXCOLUMN6PIN = 3;
int VOLTAGETHRESHOLD = 400;
int NUMBEROFSWITCHES = 6;
int BALLROGHITSTATUSARRAYPOS = 0;
int LEFTRAMPMADESTATUSARRAYPOS = 1;
int RIGHTRAMPENTERSTATUSARRAYPOS = 2;
int BALLORGOPENSTATUSARRAYPOS = 3;
int BALLORCLOSEDSTATUSARRAYPOS = 4;
int LEFTORBITLOWSTATUSARRAYPOS = 5;



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
  attachInterrupt(digitalPinToInterrupt(MATRIXCOLUMN5PIN), Column5InterruptRoutine, FALLING);
  attachInterrupt(digitalPinToInterrupt(MATRIXCOLUMN6PIN), Column6InterruptRoutine, FALLING);
  //enable serial communication to the LEDArduio to send according commands upon switches activated


}

void loop() {
    waitFor(WaitInMainLoop);
}
 
 
  void Column5InterruptRoutine(){
	  //Ballroghit is always close - a Hit opens the switch
    DEBUG_PRINT(micros());
     DEBUG_PRINT("BallrogPin Value: ");
    DEBUG_PRINTLN(analogRead(BALLORGHITPIN));
  }

  void Column6InterruptRoutine(){
    if(analogRead(LEFTRAMPMADEPIN) < VOLTAGETHRESHOLD){
      SwitchState[LEFTRAMPMADESTATUSARRAYPOS] = 1;
    }else{
	  SwitchState[LEFTRAMPMADESTATUSARRAYPOS] = 0;
	}
    if(analogRead(LEFTORBITLOWPIN) < VOLTAGETHRESHOLD){
      SwitchState[LEFTORBITLOWSTATUSARRAYPOS] = 1;
    }else{
	  SwitchState[LEFTORBITLOWSTATUSARRAYPOS] = 0;
	}
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


