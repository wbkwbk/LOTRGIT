#include <WS2812FX.h>
#include <SoftwareSerial.h>

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTDEC(x) Serial.print(x, DEC)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#endif


#define EVENTBALLORGHIT 100
#define EVENTRIGHTRAMPENTER 200
#define EVENTLEFTRAMPMADE 300
#define EVENTLEFTORBITLOW 400
#define EVENTBALLORGOPEN 500
#define EVENTBALLOROGCLOSED 600
int BALLROGHITSTATUSARRAYPOS = 0;
int LEFTRAMPMADESTATUSARRAYPOS = 1;
int RIGHTRAMPENTERSTATUSARRAYPOS = 2;
int BALLORGOPENSTATUSARRAYPOS = 3;
int BALLORCLOSEDSTATUSARRAYPOS = 4;
int LEFTORBITLOWSTATUSARRAYPOS = 5;


#define LED_PIN 10
#define LED_COUNT 60


#define RXReceivePin 8
#define TXSendPin 9
unsigned long lastTimeSwitchActived[6]={-1,-1,-1,-1,-1,-1,};
int BUTTONDEBOUNCETIME = 200;

SoftwareSerial serialComm(RXReceivePin, TXSendPin);
int currentPotVal = 0;  // Variable to store the input from the potentiometer
int previousPotVal = 0;
int potPin = A5;

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  serialComm.begin(115200);
  Serial.begin(9600);
  ws2812fx.init();
  ws2812fx.setBrightness(40);  //wertebereich von 0-255
     // Set the animation speed. 10=very fast, 5000=very slow
  ws2812fx.setSpeed(200);
  ws2812fx.setMode(FX_MODE_COLOR_WIPE);  
  ws2812fx.start();

}

void loop() {
    ws2812fx.service();
     currentPotVal = analogRead(potPin);
    if (currentPotVal > previousPotVal + 25 || currentPotVal < previousPotVal - 25) {
        previousPotVal = currentPotVal;
        currentPotVal = map(currentPotVal, 0, 1023, 0, 255);
        ws2812fx.setBrightness(currentPotVal);
        DEBUG_PRINT("Potentiometer Value: ");   
	    DEBUG_PRINTLN(currentPotVal); 
    }

    if(serialComm.available() > 0){
        int command = serialComm.parseInt();
        switch(command){
            case EVENTBALLORGHIT:
            if(checkDebounceTimePassed(BALLROGHITSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received BallroghHit: "));
                Serial.println(command);
            }
            break;

            case EVENTRIGHTRAMPENTER:
            if(checkDebounceTimePassed(RIGHTRAMPENTERSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received RightRampEnter: "));
                Serial.println(command);
            }
            break;    
            case EVENTLEFTRAMPMADE:
            if(checkDebounceTimePassed(LEFTRAMPMADESTATUSARRAYPOS, millis())){
                Serial.print(F("Command received LeftRampMade: "));
                Serial.println(command);
            }
            break;    
            case EVENTLEFTORBITLOW:
            if(checkDebounceTimePassed(LEFTORBITLOWSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received LeftorbitLow: "));
                Serial.println(command);
            }
            break;    
            case EVENTBALLORGOPEN:
            if(checkDebounceTimePassed(BALLORGOPENSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received BallrogOpen: "));
                Serial.println(command);
            }
            break;    
            case EVENTBALLOROGCLOSED:
            if(checkDebounceTimePassed(BALLORCLOSEDSTATUSARRAYPOS, millis())){
                Serial.print(F("Command received BallrogClosed: "));
                Serial.println(command);
            }
            break;    
        }
    }
}

boolean checkDebounceTimePassed(int currentSwitch, unsigned long currentTime){
    boolean timePassed=false;

    if(currentTime - lastTimeSwitchActived[currentSwitch] > BUTTONDEBOUNCETIME){
        lastTimeSwitchActived[currentSwitch] = currentTime;
        timePassed = true;   
    }
    return timePassed;
}