#include <SoftwareSerial.h>   //We are using software serial so as not to conflict with serial download and monitor


#define LEDRXReceivePin 8
#define LEDTXSendPin 9



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


SoftwareSerial LEDserialComm(LEDRXReceivePin,LEDTXSendPin); // RX, TX


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
  LEDserialComm.begin(115200);

}

void loop() {
    waitFor(WaitInMainLoop);
    for (int i = 0 ; i < NUMBEROFSWITCHES; i += 1) {
        if(SwitchState[i] == 1){
		    if(i != BALLROGHITSTATUSARRAYPOS && i != BALLORGOPENSTATUSARRAYPOS && i != BALLORCLOSEDSTATUSARRAYPOS){
			    DEBUG_PRINT(Switchnames[i]);
			    DEBUG_PRINTLN(" is closed");
		    }
	    }else if(i==BALLROGHITSTATUSARRAYPOS && SwitchState[BALLROGHITSTATUSARRAYPOS] == 0){
		    DEBUG_PRINTLN("Ballrog is Hit"); 
        }

    }
        if(BallRogOpen){
            DEBUG_PRINT(millis());
            DEBUG_PRINTLN(":Ballrog is OPEN");     
        }else{
            DEBUG_PRINT(millis());
            DEBUG_PRINTLN(":Ballrog is CLOSED");
        }}

  void Column5InterruptRoutine(){
	  //Ballroghit is always close - a Hit opens the switch
    DEBUG_PRINT(micos();
     DEBUG_PRINT(BallrogPin Value:);

    if(analogRead(BALLORGHITPIN) <  VOLTAGETHRESHOLD){
      SwitchState[BALLROGHITSTATUSARRAYPOS] = 1;
    }else{
	  SwitchState[BALLROGHITSTATUSARRAYPOS] = 0;
    LEDserialComm.println(EVENTBALLORGHIT);
	}
	//DEBUG_PRINT("Analog Value of RIGHTRAMPENTERPIN: ");
	//DEBUG_PRINTLN(analogRead(RIGHTRAMPENTERPIN));
    if(analogRead(RIGHTRAMPENTERPIN) < VOLTAGETHRESHOLD){
      SwitchState[RIGHTRAMPENTERSTATUSARRAYPOS] = 1;
      LEDserialComm.println(EVENTRIGHTRAMPENTER);
    }else{
	  SwitchState[RIGHTRAMPENTERSTATUSARRAYPOS] = 0;
	}
    if(analogRead(BALLORGOPENPIN) < VOLTAGETHRESHOLD){
      if(SwitchState[BALLORGOPENSTATUSARRAYPOS] == 0){
        //First time  Ballrog is open send the information
        BallRogOpen = false;
        LEDserialComm.println(EVENTBALLOROGCLOSED);
      }
      SwitchState[BALLORGOPENSTATUSARRAYPOS] = 1;
    }else{
	  SwitchState[BALLORGOPENSTATUSARRAYPOS] = 0;
	}
    if(analogRead(BALLOROGCLOSEDPIN) < VOLTAGETHRESHOLD){
      if(SwitchState[BALLORCLOSEDSTATUSARRAYPOS] == 0){
        //First time  Ballrog is closed send the information
        BallRogOpen = true;
        LEDserialComm.println(EVENTBALLROGOPEN);  
      }
      SwitchState[BALLORCLOSEDSTATUSARRAYPOS] = 1;
    }else{
	  SwitchState[BALLORCLOSEDSTATUSARRAYPOS] = 0;
	}
  }
  void Column6InterruptRoutine(){
    if(analogRead(LEFTRAMPMADEPIN) < VOLTAGETHRESHOLD){
      SwitchState[LEFTRAMPMADESTATUSARRAYPOS] = 1;
      LEDserialComm.println(EVENTLEFTRAMPMADE);
    }else{
	  SwitchState[LEFTRAMPMADESTATUSARRAYPOS] = 0;
	}
    if(analogRead(LEFTORBITLOWPIN) < VOLTAGETHRESHOLD){
      SwitchState[LEFTORBITLOWSTATUSARRAYPOS] = 1;
      LEDserialComm.println(EVENTLEFTORBITLOW);
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


