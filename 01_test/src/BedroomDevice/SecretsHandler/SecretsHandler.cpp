#include "SecretsHandler.h"


SecretsHandler::SecretsHandler()
{
}

// Destructor (if needed)
SecretsHandler::~SecretsHandler() {
}

ErrorCode SecretsHandler::init(){
    if(!SPIFFS.begin(true)){
        return SPIFFS_BEGIN_ERRROR;
    }
    return SUCCESS;
}

ErrorCode SecretsHandler::readConfig(){
    File file = SPIFFS.open("/config.json");
    if (!file) {
        return CONFIG_FILE_OPEN_READ_ERROR;
    }
    if (!SPIFFS.exists("/config.json")) {
        return CONFIG_FILE_EXIST_ERROR;
    }
    size_t size = file.size();
    std::unique_ptr<char[]> buf(new char[size]);
    file.readBytes(buf.get(), size);

    DynamicJsonDocument jsonBuffer(2048);
    DeserializationError error = deserializeJson(jsonBuffer, buf.get());
    if (error) {
        return JSON_PARSE_ERROR;
    }
    access_token = jsonBuffer["access_token"].as<String>();
    refresh_token = jsonBuffer["refresh_token"].as<String>();
    client_id = jsonBuffer["client_id"].as<String>();
    client_secret = jsonBuffer["client_secret"].as<String>();
    ssid = jsonBuffer["ssid"].as<String>();
    password = jsonBuffer["password"].as<String>();
    return SUCCESS;
}

ErrorCode SecretsHandler::writeConfig(){
    DynamicJsonDocument jsonBuffer(1024);
    jsonBuffer["access_token"] = access_token;
    jsonBuffer["refresh_token"] = refresh_token;
    jsonBuffer["client_id"] = client_id;
    jsonBuffer["client_secret"] = client_secret;
    jsonBuffer["ssid"] = ssid;
    jsonBuffer["password"] = password;

    File file = SPIFFS.open("/config.json", FILE_WRITE);
    if (!file) {
        return CONFIG_FILE_OPEN_WRITE_ERROR;
    }
    serializeJson(jsonBuffer, file);
    return SUCCESS;
}