/*
    PressureChecker.h - Library for monitoring pressure values from analog pin
    Created by Robert Hoffmann, 2022
*/

#ifndef PressureChecker_h
#define PressureChecker_h

#include <Arduino.h>

class PressureChecker{
private:
    const int _pin = 34;
    const float _criticalThreshold = 2;
    float _pressureReading = 0;
    float _voltage = 0;
    float _pressure_bar = 0;
    unsigned long _start_time; 
    unsigned long _timed_event;
    unsigned long _current_time;

    void getActualPressureReading();
public:
    PressureChecker();
    bool isCritical();
    float getPressure();

};

#endif