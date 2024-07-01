#ifndef BEDROOM_DEVICE_H
#define BEDROOM_DEVICE_H

#include"LcdHandler/LcdHandler.h"
#include "SecretsHandler/SecretsHandler.h"
#include "ErrorCodes/ErrorCodes.h"
#include "WifiHandler/WifiHandler.h"
#include"StravaHandler/StravaHandler.h"

class BedroomDevice
{
private:
public:
    ErrorCode error;
    LcdHandler lcd;
    SecretsHandler secretsHandler;
    WifiHandler wifiHandler;
    StravaHandler stravaHandler;
    BedroomDevice();
    ~BedroomDevice();
    ErrorCode init();
};

#endif //BEDROOM_DEVICE_H

