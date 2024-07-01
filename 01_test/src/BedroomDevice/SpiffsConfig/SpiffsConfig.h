#ifndef SPIFFSCONFIG_H
#define SPIFFSCONFIG_H

#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <Arduino.h>

extern String accessToken, refreshToken, clientId, clientSecret, ssid, password;

void readConfig();
void saveConfig();

#endif // SPIFFSCONFIG_H