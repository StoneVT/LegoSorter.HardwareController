/*
    PressureChecker.h - Library for monitoring pressure values from analog pin
    Created by Robert Hoffmann, 2022
*/

#include "PressureChecker.h"

//TODO: initialize _pin, _criticalThreshold and intervall_sec over constructor
//(const int pin, const float criticalThreshold, const int intervall_sec)
PressureChecker::PressureChecker(const int pin, const float criticalThreshold, const int intervall_sec) 
: _pin(pin), _criticalThreshold(criticalThreshold), _timed_event(1000 * intervall_sec), _current_time(millis()), _start_time(_current_time)
{
}

void PressureChecker::CheckPressure()
{
    if (isCritical())
    {
        Notify();
    }
}

void PressureChecker::getActualPressureReading(){
    this->_pressureReading = analogRead(this->_pin);
    this->_voltage = (this->_pressureReading * 0.0008) + 0.1754;
    this->_pressure_bar = (this->_pressureReading * 0.0022) - 1.0257;  
}

bool PressureChecker::isCritical(){
    this->_current_time = millis(); // update the timer every cycle

	if (this->_current_time - this->_start_time >= this->_timed_event) {
        this->_start_time = this->_current_time;  // reset the timer
        
		getActualPressureReading();

        if(this->_pressure_bar<=this->_criticalThreshold)
            return 1;
        else
            return 0;

	}
    return 0;
}

void PressureChecker::Notify(){
    event::PressureCriticalEvent e(_criticalThreshold, _pressure_bar);

    for (auto& eventHandler : eventHandlers_)
    {
        eventHandler->HandleEvent(&e);
    }
}
