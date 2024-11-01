#include <SoftwareSerial.h>

const int flamePin = 7; // Flame sensor pin
SoftwareSerial BTSerial(10, 11); // RX, TX for HC-06

void setup() {
  pinMode(flamePin, INPUT); // Set the flame sensor pin as input
  Serial.begin(9600);       // Start Serial Monitor for debugging
  BTSerial.begin(9600);     // Start HC-06 Bluetooth at 9600 baud
}

void loop() {
  int flameState = digitalRead(flamePin);

  if (flameState == LOW) {  // Flame detected (LOW)
    Serial.println("Flame Detected!");
    BTSerial.println("Alert! Flame detected."); // Send alert to phone
    delay(1000); // Prevent flooding messages every loop
  } 
  else if(flameState == HIGH) {
    Serial.println("No Flame Detected.");
    BTSerial.println("No Flame Detected.");
    delay(1000); // Check every second
  }
}
