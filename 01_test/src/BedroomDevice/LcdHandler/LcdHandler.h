#ifndef LCD_HANDLER_H
#define LCD_HANDLER_H

#include <LiquidCrystal.h>
#include "ErrorCodes/ErrorCodes.h"

#include <Arduino.h>

class LcdHandler
{
private:
    static const int rs = 16, en = 17, d4 = 18, d5 = 19, d6 = 21, d7 = 22;
    LiquidCrystal lcd;
public:
    LcdHandler();  // Constructor
    ~LcdHandler(); // Destructor
    ErrorCode init();
    ErrorCode write(const String& msg, int row, int delayTime);
};






#endif //LCD_HANDLER_H
