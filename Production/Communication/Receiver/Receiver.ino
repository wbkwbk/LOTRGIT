#include <SoftwareSerial.h>

// Definiere die Pins für SoftwareSerial (die Pins 8 und 9)
#define RXPIN 51 //connect  the Switch Receiving D0 to the SwitchstateDedector Sender D6
#define TXPIN 53 //connect the Switch transmitting D1 to the SwitchtstateDedector Receiver D0

SoftwareSerial mySerial(RXPIN, TXPIN);  // Erstelle ein SoftwareSerial-Objekt

void setup() {
  // Starte die serielle Kommunikation mit dem PC und mit dem Uno
  Serial.begin(9600);  // Serielle Kommunikation mit dem PC
  mySerial.begin(9600);  // Serielle Kommunikation mit dem Uno

  // Ein kleiner Delay, um sicherzustellen, dass alles initialisiert ist
  delay(1000);
}

void loop() {
  // Überprüfe, ob Daten vom Uno empfangen wurden
  if (mySerial.available() > 0) {
    int receivedValue = mySerial.parseInt();  // Lese den Wert
    Serial.print("Empfangener Wert: ");
    Serial.println(receivedValue);  // Zeige den empfangenen Wert im Serial Monitor an
  }
}