#ifndef GMAIL_HANDLER_H
#define GMAIL_HANDLER_H

#include <LiquidCrystal.h>
#include "ErrorCodes/ErrorCodes.h"

#include <Arduino.h>

class GmailHandler
{
private:
    
public:
    int unread_emails;
    
    GmailHandler();  // Constructor
    ~GmailHandler(); // Destructor
    ErrorCode init();
    ErrorCode getUnread();
};






#endif //LCD_HANDLER_H
