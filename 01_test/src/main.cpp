#include <Arduino.h>

// Define the LED pin
const int LED_PIN = 0;

void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_PIN, HIGH);
  // Wait for a second
  delay(500);
  // Turn the LED off by making the voltage LOW
  digitalWrite(LED_PIN, LOW);
  // Wait for a second
  delay(500);
}
