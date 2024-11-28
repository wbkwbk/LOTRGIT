int ledPin = 9;  // Pin connected to the LED (Pin 13 is commonly used on many Arduino boards)

void setup() {
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
}

void loop() {
  unsigned long startMillis = millis();  // Save the start time
  while (millis() - startMillis < 10000) {  // Run the effect for 10 seconds (10000 milliseconds)
    // Randomize the duration of LED flashes to simulate lightning
    int flashDuration = random(10, 100);  // Random delay between 10 ms and 100 ms
    
    // LED on
    digitalWrite(ledPin, HIGH);
    delay(flashDuration);  // Keep LED on for the random duration
    
    // LED off
    digitalWrite(ledPin, LOW);
    delay(flashDuration);  // Keep LED off for the same random duration
  }

  // After 10 seconds, the effect stops, and the loop starts over again (if desired).
}