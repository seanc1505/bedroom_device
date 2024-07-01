#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include <LiquidCrystal.h>
#include <SPIFFS.h>
#include <SPI.h>
#include <Wire.h>


#include <Arduino.h>

#include "BedroomDevice/BedroomDevice.h"
#include "ErrorCodes/ErrorCodes.h"


BedroomDevice bedroomDevice;
ErrorCode error = SUCCESS;


void setup() {
    // Initialize the serial communication for debugging
    Serial.begin(9600);
    // Call the setup method of the BedroomDevice
    bedroomDevice = BedroomDevice();

    error = bedroomDevice.init();
    if (error != SUCCESS) {
        Serial.println(error);
        }
        else {Serial.println("bedroom device running as expected");}
    
}

void loop() {


    
    error = bedroomDevice.wifiHandler.tempTestWifi();
    if  (error != SUCCESS){Serial.println(error);}

    error = bedroomDevice.lcd.write(bedroomDevice.wifiHandler.current_date_time, 0, 500);  
    if  (error != SUCCESS){Serial.println(error);}
   
    delay(2000);
    error = bedroomDevice.lcd.write(bedroomDevice.stravaHandler.activity.sport_type,1,500);
    if  (error != SUCCESS){Serial.println(error);}
    delay(2000);
    String msg = "Name: " + bedroomDevice.stravaHandler.activity.name + "\n" + "Distance: " + String(bedroomDevice.stravaHandler.activity.distance/1000) + " km \nSuffer :" + String(bedroomDevice.stravaHandler.activity.suffer_score); 
    bedroomDevice.lcd.write(msg,0,500);
    if  (error != SUCCESS){Serial.println(error);}
    
    delay(150000);  // Wait for 2 seconds before running again

}

