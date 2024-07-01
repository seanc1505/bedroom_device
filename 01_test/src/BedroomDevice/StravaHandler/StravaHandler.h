#ifndef STRAVA_HANDLER_H
#define STRAVA_HANDLER_H

#include "ErrorCodes/ErrorCodes.h"

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include "BedroomDevice/SecretsHandler/SecretsHandler.h"
#include "stravaActivity.h"
class StravaHandler
{
private:
    SecretsHandler* secretsHandler;
public:
    String strava_data = "";
    String lcd_strava_string; 
    stravaActivity activity;
    StravaHandler();  // Constructor
    ~StravaHandler(); // Destructor
    ErrorCode init(SecretsHandler* secrets);
    ErrorCode refreshAccessToken();
    ErrorCode getLatestActivity();
};






#endif //STRAVA_HANDLER_H
