/*
    TimestampModifier.h - Library for modifiying a unix timestamp with a precision of milliseconds
    Created by Robert Hoffmann, 2022
*/
#include "TimestampModifier.h"

TimestampModifier::TimestampModifier(){

}

String TimestampModifier::getUnixTimeStamp(){
    String milliEpoch = "";
    int tries = 1;
    do {
        char buffer [3];
        unsigned long ms_time = ms();
        sprintf(buffer,"%03d",ms_time);
        milliEpoch = String(now()) + buffer;
        if(tries > 1) {
        delay(1);
        Serial.println("[TIME]\tGetting unix timestamp. Try: " + String(tries) + " Length: " + String(milliEpoch.length()));
        }
        tries += 1;
        } while (milliEpoch.length() != 13);
        
        return milliEpoch.substring(0,13);
    }

long TimestampModifier::cutTimeStampTolong(String timestamp){
    if(timestamp.length() < 9) {
        return timestamp.toInt();
    }
    String tmp = timestamp.substring(4,13);
    return tmp.toInt();
    }