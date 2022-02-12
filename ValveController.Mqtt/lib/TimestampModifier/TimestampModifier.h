/*
    TimestampModifier.h - Library for modifiying a unix timestamp with a precision of milliseconds
    Created by Robert Hoffmann, 2022
*/

#ifndef TimestampModifier_h
#define TimestampModifier_h

#include <Arduino.h>
#include <ezTime.h>

class TimestampModifier{
public:
    TimestampModifier();
    String getUnixTimeStamp();
    long cutTimeStampTolong(String timestamp);

};

#endif