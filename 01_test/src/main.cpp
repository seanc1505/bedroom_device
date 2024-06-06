#include <Arduino.h>
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// LiquidCrystal lcd(34, 35, 26, 27, 14, 12);
const int rs = 16, en = 17, d4 = 18, d5 = 19, d6 = 21, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int ledPin = 5;

void setup() {
    lcd.begin(16, 2);  // set up the LCD's number of columns and rows
    lcd.print("Hello, World!");  // Print a message to the LCD

  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  delay(1000); // Keep the LED on for 1 second
  lcd.clear();
  lcd.print("Hello, World!");
  for(int i = 0; i < 11; i++) {
    lcd.setCursor(0, 1);
    lcd.print(i);
    delay(100);
  }
  // lcd.print("Hello, ESP32!");
  // Turn the LED off
  digitalWrite(ledPin, LOW);
  delay(1000); // Keep the LED off for 1 second
  // lcd.clear();
}
