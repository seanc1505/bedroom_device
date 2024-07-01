#ifndef SECRETS_HANDLER_H
#define SECRETS_HANDLER_H


#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#include "ErrorCodes/ErrorCodes.h"

class SecretsHandler
{
private:


public:
    String access_token, refresh_token, client_id, client_secret, ssid, password;
    SecretsHandler();
    ~SecretsHandler();
    ErrorCode init();
    ErrorCode readConfig();
    ErrorCode writeConfig();
};

#endif //SECRETS_HANDLER_H

