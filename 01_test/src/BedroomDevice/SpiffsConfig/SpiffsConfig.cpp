#include "SpiffsConfig.h"


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