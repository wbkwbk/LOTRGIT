#include <SoftwareSerial.h>   //We are using software serial so as not to conflict with serial download and monitor
#include <WS2812FX.h>

#define RXReceivePin 8
#define TXSendPin 9

#define LED_PIN 10
#define LED_COUNT 60

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
int WaitInMainLoop = 100;
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


SoftwareSerial serialComm(RXReceivePin,TXSendPin); // RX, TX
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

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
  

  //enable serial communication to the soundshield to send according commands upon switches activated
  serialComm.begin(115200);
  ws2812fx.init();
  ws2812fx.setBrightness(200);  //wertebereich von 0-255
     // Set the animation speed. 10=very fast, 5000=very slow
  ws2812fx.setSpeed(200);
  ws2812fx.setMode(FX_MODE_COLOR_WIPE); 
  DEBUG_PRINTLN("starting"); 
}

void loop() {
    waitFor(WaitInMainLoop);
    CheckSwitches();
/*
    for (int i = 0 ; i < NUMBEROFSWITCHES; i += 1) {
        if(SwitchState[i] == 1){
		    if(i != BALLROGHITSTATUSARRAYPOS && i != BALLORGOPENSTATUSARRAYPOS && i != BALLORCLOSEDSTATUSARRAYPOS){
			    DEBUG_PRINT(Switchnames[i]);
			    DEBUG_PRINTLN(" is closed");
		    }
	    }else if(i==BALLROGHITSTATUSARRAYPOS && SwitchState[BALLROGHITSTATUSARRAYPOS] == 0){
		    DEBUG_PRINTLN("Ballrog is Hit"); 
        }
        if(BallRogOpen){
            DEBUG_PRINTLN("Ballrog is OPEN");     
        }else{
            DEBUG_PRINTLN("Ballrog is CLOSED");
        }
    }
*/
}

  void CheckSwitches(){
	  //Ballroghit is always close - a Hit opens the switch
    if(analogRead(BALLORGHITPIN) <  VOLTAGETHRESHOLD){
      SwitchState[BALLROGHITSTATUSARRAYPOS] = 1;
    }else{
	  SwitchState[BALLROGHITSTATUSARRAYPOS] = 0;
      serialComm.println(EVENTBALLORGHIT);
	}
	//DEBUG_PRINT("Analog Value of RIGHTRAMPENTERPIN: ");
	//DEBUG_PRINTLN(analogRead(RIGHTRAMPENTERPIN));
    if(analogRead(RIGHTRAMPENTERPIN) < VOLTAGETHRESHOLD){
      SwitchState[RIGHTRAMPENTERSTATUSARRAYPOS] = 1;
      serialComm.println(EVENTRIGHTRAMPENTER);
    }else{
	  SwitchState[RIGHTRAMPENTERSTATUSARRAYPOS] = 0;
	}
    if(analogRead(BALLORGOPENPIN) < VOLTAGETHRESHOLD){
      if(SwitchState[BALLORGOPENSTATUSARRAYPOS] == 0){
        //First time  Ballrog is open send the information
        BallRogOpen = false;
        serialComm.println(EVENTBALLOROGCLOSED);
      }
      SwitchState[BALLORGOPENSTATUSARRAYPOS] = 1;
    }else{
	  SwitchState[BALLORGOPENSTATUSARRAYPOS] = 0;
	}
    if(analogRead(BALLOROGCLOSEDPIN) < VOLTAGETHRESHOLD){
      if(SwitchState[BALLORCLOSEDSTATUSARRAYPOS] == 0){
        //First time  Ballrog is closed send the information
        BallRogOpen = true;
        serialComm.println(EVENTBALLROGOPEN);  
      }
      SwitchState[BALLORCLOSEDSTATUSARRAYPOS] = 1;
    }else{
	  SwitchState[BALLORCLOSEDSTATUSARRAYPOS] = 0;
	}
    int leftRampPinAnalogValue = analogRead(LEFTRAMPMADEPIN);
 	DEBUG_PRINT("Analog Value of LEFTRAMPMADEPIN: ");
	DEBUG_PRINTLN(leftRampPinAnalogValue);   
    if(leftRampPinAnalogValue < VOLTAGETHRESHOLD){
      SwitchState[LEFTRAMPMADESTATUSARRAYPOS] = 1;
      serialComm.println(EVENTLEFTRAMPMADE);
    }else{
	  SwitchState[LEFTRAMPMADESTATUSARRAYPOS] = 0;
	}
    if(analogRead(LEFTORBITLOWPIN) < VOLTAGETHRESHOLD){
      SwitchState[LEFTORBITLOWSTATUSARRAYPOS] = 1;
      serialComm.println(EVENTLEFTORBITLOW);
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
/*	    while (serialComm.available() == 0) { 
            ws2812fx.service(); 
	    }
	    int potValue = serialComm.parseInt();
	    DEBUG_PRINT("Potentiometer Value: ");   
	    DEBUG_PRINTLN(potValue);   
        ws2812fx.setBrightness(potValue);
*/    //todo add timer for led-stripe animation run duration 
    }
}


