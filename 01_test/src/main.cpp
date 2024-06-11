#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPIFFS.h>
#include <SPI.h>
#include <Wire.h>

const int rs = 16, en = 17, d4 = 18, d5 = 19, d6 = 21, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String ssid ;
String password;
const int ledPin = 15;
String accessToken, refreshToken, clientId, clientSecret;

void readConfig() {
    File file = SPIFFS.open("/config.json");
    if (!file) {
        Serial.println("Failed to open config file");
        return;
    }

    size_t size = file.size();
    std::unique_ptr<char[]> buf(new char[size]);
    file.readBytes(buf.get(), size);

    DynamicJsonDocument jsonBuffer(1024);
    DeserializationError error = deserializeJson(jsonBuffer, buf.get());
    if (error) {
        Serial.println("Failed to parse config file");
        return;
    }
    accessToken = jsonBuffer["access_token"].as<String>();
    refreshToken = jsonBuffer["refresh_token"].as<String>();
    clientId = jsonBuffer["client_id"].as<String>();
    clientSecret = jsonBuffer["client_secret"].as<String>();
}

void saveConfig() {
    DynamicJsonDocument jsonBuffer(1024);
    jsonBuffer["access_token"] = accessToken;
    jsonBuffer["refresh_token"] = refreshToken;
    jsonBuffer["client_id"] = clientId;
    jsonBuffer["client_secret"] = clientSecret;

    File file = SPIFFS.open("/config.json", FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open config file for writing");
        return;
    }
    serializeJson(jsonBuffer, file);
}

bool refreshAccessToken() {
    HTTPClient http;
    http.begin("https://www.strava.com/oauth/token");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "client_id=" + clientId + "&client_secret=" + clientSecret +
                      "&grant_type=refresh_token&refresh_token=" + refreshToken;

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
        String payload = http.getString();
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return false;
        }
        accessToken = doc["access_token"].as<String>();
        refreshToken = doc["refresh_token"].as<String>();
        saveConfig();  // Save the new tokens
        Serial.println("Access token refreshed");
        return true;
    } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpResponseCode);
        return false;
    }

    http.end();
}
void scrollText(String msg, int row, int delayTime) {
    int len = msg.length();
    int pos = 0;
    int displayWidth = 16;

    while (pos <= len - displayWidth) {
        lcd.clear();
        lcd.setCursor(0, row);
        lcd.print(msg.substring(pos, pos + displayWidth));
        pos++;
        delay(delayTime);
    }
}


void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
    lcd.begin(16, 2);  // set up the LCD's number of columns and rows
    lcd.print("Hello, World!");  // Print a message to the LCD

    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    File file = SPIFFS.open("/config.json");
    if(!file){
        Serial.println("Failed to open config file");
        return;
    }

    size_t size = file.size();
    std::unique_ptr<char[]> buf(new char[size]);
    file.readBytes(buf.get(), size);

    DynamicJsonDocument jsonBuffer(1024);
    DeserializationError error = deserializeJson(jsonBuffer, buf.get());
    if (error) {
        Serial.println("Failed to parse config file");
        return;
    }
    accessToken = jsonBuffer["access_token"].as<String>();
    ssid = jsonBuffer["ssid"].as<String>();
    password = jsonBuffer["password"].as<String>();

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        lcd.clear();
        lcd.print("Connecting to WiFi...");
        Serial.println("Connecting to WiFi...");
    }
    lcd.clear();
    Serial.println("Connected to WiFi");
    lcd.print("WiFi Connected");
}


void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("https://www.strava.com/api/v3/athlete/activities?page=1&per_page=1");  // Specify the URL
        http.addHeader("Authorization", "Bearer " + accessToken);

        int httpResponseCode = http.GET();  // Send the request

        if (httpResponseCode > 0) {
            String payload = http.getString();
            lcd.clear();
            Serial.println("HTTP Response payload: " + payload);

            // Increase the size of the DynamicJsonDocument
            const size_t capacity = 8192; // Increased capacity based on the size of your payload
            DynamicJsonDocument doc(capacity);

            DeserializationError error = deserializeJson(doc, payload);

            if (error) {
              Serial.print("deserializeJson() failed: ");
              Serial.println(error.c_str());
              lcd.clear();
              lcd.print("JSON Error");
              return;
            }
            const char* activity_name = doc[0]["name"];
            Serial.print("Act Name: ");
            Serial.println(activity_name);
            
            String displayText = "Act Name: " + String(activity_name);
            scrollText(displayText, 0, 250);  // Scroll the text on the first row with a delay of 250 ms


        } else {
            Serial.print("Error on HTTP request: ");
            Serial.println(httpResponseCode);
            lcd.clear();
            lcd.print("HTTP Error");
        }

        http.end();  // Free resources
    } else {
        Serial.println("WiFi Disconnected");
        lcd.clear();
        lcd.print("WiFi Disconnected");
    }

    digitalWrite(ledPin, LOW);
    delay(1000); // Keep the LED off for 1 second
    digitalWrite(ledPin, HIGH);
    delay(1000000); // Keep the LED on for 1 second
    digitalWrite(ledPin, LOW);
    delay(100); // Keep the LED off for 1 second
    digitalWrite(ledPin, HIGH);
    delay(1000); // Keep the LED on for 1 second
}
