
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

void setup() {
  Serial.begin(115200);
}

void loop() {
    DEBUG_PRINT("Actual Micro:");   
    DEBUG_PRINTLN(micros()); 
}