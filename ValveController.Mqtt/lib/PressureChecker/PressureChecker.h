/*
    PressureChecker.h - Library for monitoring pressure values from analog pin
    Created by Robert Hoffmann, 2022
*/

#ifndef PressureChecker_h
#define PressureChecker_h

#include <Arduino.h>
#include "Event.h"

class PressureChecker : public event::EventHandler {
private:
    const int _pin{34};
    const float _criticalThreshold{2};
    unsigned long _timed_event{0};
    float _pressureReading{0};
    float _voltage{0};
    float _pressure_bar{0};
    unsigned long _current_time{0};
    unsigned long _start_time{0}; 
    

    void getActualPressureReading();
    bool isCritical();

public:
    PressureChecker() = default;
    PressureChecker(const int pin, const float criticalThreshold, const int intervall_sec);
    void CheckPressure();

protected:
    void Notify() override;

};

#endif