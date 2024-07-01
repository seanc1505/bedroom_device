#include "LcdHandler.h"

LcdHandler::LcdHandler() : lcd(rs, en, d4, d5, d6, d7) {}

LcdHandler::~LcdHandler(){

}

ErrorCode LcdHandler::init() {
    lcd.begin(16, 2);  // Set up the LCD's number of columns and rows    
    return SUCCESS;
}

ErrorCode LcdHandler::write(const String& msg, int row, int delayTime) {
    int len = msg.length();
    int displayWidth = 16;

    if (len<= displayWidth){
        lcd.clear();
        lcd.setCursor(0, row);
        lcd.print(msg);
    }
    else{
        for (int pos = 0; pos <= (len-displayWidth); pos++) {
            lcd.clear();
            lcd.setCursor(0, row);
            if (pos <= len - displayWidth) {
                lcd.print(msg.substring(pos, pos + displayWidth));
            } else {
                lcd.print(msg.substring(pos));
            }
            delay(delayTime);
        }
    }

    return SUCCESS;
}




