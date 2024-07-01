#include "BedroomDevice.h"

BedroomDevice::BedroomDevice()
    : lcd(), secretsHandler(), wifiHandler(), stravaHandler() {
}

BedroomDevice::~BedroomDevice() {}

ErrorCode BedroomDevice::init(){
    
    error = lcd.init();
    if (error != SUCCESS) return error;
    error = secretsHandler.init();
    if (error != SUCCESS) return error;
    error = secretsHandler.readConfig();
    if (error != SUCCESS) return error;
    error = wifiHandler.init(secretsHandler.ssid,secretsHandler.password);
    if (error != SUCCESS) return error;
    error = stravaHandler.init(&secretsHandler);
    if (error != SUCCESS) return error;
    return  SUCCESS;
}
