#include "WifiHandler.h"

// Constructor
WifiHandler::WifiHandler()
{}

// Destructor (if needed)
WifiHandler::~WifiHandler() {
    // Cleanup code here (if any)
}
ErrorCode WifiHandler::init(String ssid, String password){
    // WiFi.begin(ssid, password);
    
    unsigned long startTime = millis();
    const unsigned long timeout = 45000; // 45 seconds
    WiFi.begin(ssid,password);
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startTime >= timeout) {
            return WIFI_CANT_CONNECT;
        }
        delay(500); // Short delay to prevent busy looping
    }
    return SUCCESS;
}



ErrorCode WifiHandler::tempTestWifi(){
    HTTPClient http;
    http.begin("http://worldtimeapi.org/api/timezone/Etc/UTC"); // Specify the URL
    int httpCode = http.GET(); // Make the request

    if (httpCode > 0) { // Check for the returning code
        String payload = http.getString(); // Get the request response payload
        int startIndex = payload.indexOf("\"datetime\":\"") + 12;
        int endIndex = payload.indexOf(".", startIndex);
        String datetime = payload.substring(startIndex, endIndex);
        http.end(); // Close connection
        current_date_time = datetime;
        return SUCCESS;
    } else {
        http.end(); // Close connection
        return HTTP_REQUEST_ERROR;
    }

}

