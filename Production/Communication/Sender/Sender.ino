#include <SoftwareSerial.h>

// Definiere die Pins für die SoftwareSerial-Verbindung
#define RXPIN 10 
#define TXPIN 11

// Erstelle eine SoftwareSerial-Instanz
SoftwareSerial mySerial(RXPIN, TXPIN);

void setup() {
  // Starte die serielle Kommunikation mit dem Mega und dem PC
  Serial.begin(9600);
  mySerial.begin(9600);  // Beginnt die SoftwareSerial-Kommunikation

  // Warte kurz, damit alles initialisiert ist
  delay(1000);
}

void loop() {
  // Sende den Wert 42 alle 5 Sekunden
  mySerial.println(42);
  Serial.println("Wert 42 gesendet an Mega");

  delay(5000);  // Warten für 5 Sekunden
}