#include "StravaHandler.h"


StravaHandler::StravaHandler() : secretsHandler(nullptr) {
}
// Destructor (if needed)
StravaHandler::~StravaHandler() {
    // Cleanup code here (if any)
}

ErrorCode StravaHandler::init(SecretsHandler* secrets){
    secretsHandler = secrets;
    ErrorCode error = getLatestActivity();
    return SUCCESS;
}

ErrorCode StravaHandler::refreshAccessToken(){
    HTTPClient http;
    http.begin("https://www.strava.com/oauth/token");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String postData = "client_id=" + secretsHandler->client_id + "&client_secret=" + secretsHandler->client_secret +
                      "&grant_type=refresh_token&refresh_token=" + secretsHandler->refresh_token;
    int httpResponseCode = http.POST(postData);
    http.end();
    if (httpResponseCode > 0) {
        String payload = http.getString();
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            return DESERIALIZE_JSON_ERROR;
        }
        secretsHandler->access_token = doc["access_token"].as<String>();
        secretsHandler->refresh_token = doc["refresh_token"].as<String>();
        ErrorCode secrets_error = secretsHandler->writeConfig();
        if (secrets_error != SUCCESS) return secrets_error;
        {return SUCCESS;}

    } else {
        return HTTP_REQUEST_ERROR;
    }
    

}


ErrorCode StravaHandler::getLatestActivity(){
    // if wifi connected
    HTTPClient http;

    http.begin("https://www.strava.com/api/v3/athlete/activities?page=1&per_page=1");  // Specify the URL
    http.addHeader("Authorization", "Bearer " + secretsHandler->access_token);
    int httpResponseCode = http.GET();  // Send the request
    http.end();  // Free resources
    if (httpResponseCode > 0) {
        strava_data = http.getString();
        const size_t capacity = 8192; 
        DynamicJsonDocument doc(capacity);

        DeserializationError error = deserializeJson(doc, strava_data);
        if (error) {
            return DESERIALIZE_JSON_ERROR;
        }
        const char* testing = doc["message"];
        if (String(testing) == "Authorization Error"){
            ErrorCode erroring  = refreshAccessToken();
            
            if (erroring != SUCCESS) return erroring;
            erroring =  getLatestActivity();
            if (erroring != SUCCESS) return erroring;
            return SUCCESS;

        }
        if (doc[0].containsKey("name")){
            // Populate the activity struct
            activity.name = doc[0]["name"].as<String>();
            activity.distance = doc[0]["distance"].as<float>();
            activity.moving_time = doc[0]["moving_time"].as<int>();
            activity.elapsed_time = doc[0]["elapsed_time"].as<int>();
            activity.sport_type = doc[0]["sport_type"].as<String>();
            activity.kudos_count = doc[0]["kudos_count"].as<int>();
            activity.suffer_score = doc[0]["suffer_score"].as<float>();

            return SUCCESS;
        }
        else {return STRAVA_PAYLOAD_ERROR;}
        

    } else {
            return HTTP_REQUEST_ERROR;
        }

}