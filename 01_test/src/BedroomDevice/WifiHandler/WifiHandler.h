#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include "ErrorCodes/ErrorCodes.h"
#include "Arduino.h"
#include <WiFi.h>
#include <HTTPClient.h>


class WifiHandler
{
private:
public:
    WifiHandler(/* args */);
    ~WifiHandler();
    ErrorCode init(String ssid, String password);
    ErrorCode tempTestWifi();
    String current_date_time;
};

#endif //WIFI_HANDLER_H

