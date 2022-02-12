/*
    PressureChecker.h - Library for monitoring pressure values from analog pin
    Created by Robert Hoffmann, 2022
*/

#include "PressureChecker.h"

//TODO: initialize _pin, _criticalThreshold and intervall_sec over constructor
//(const int pin, const float criticalThreshold, const int intervall_sec)
PressureChecker::PressureChecker(){
   // this->_pin = pin;
   // this->_criticalThreshold = criticalThreshold;
   // this->_intervall_sec = intervall_sec
    int intervall_sec = 60;
    this->_timed_event = intervall_sec * 1000;
    this->_current_time = millis();
	this->_start_time = this->_current_time;
}

void PressureChecker::getActualPressureReading(){
    this->_pressureReading = analogRead(this->_pin);
    this->_voltage = (this->_pressureReading * 0.0008) + 0.1754;
    this->_pressure_bar = (this->_pressureReading * 0.0022) - 1.0257;  
}

bool PressureChecker::isCritical(){
    this->_current_time = millis(); // update the timer every cycle

	if (this->_current_time - this->_start_time >= this->_timed_event) {
		getActualPressureReading();
        if(this->_pressure_bar<=this->_criticalThreshold)
            return 1;
        else
            return 0;
		this->_start_time = this->_current_time;  // reset the timer
	}
    return 0;
}

float PressureChecker::getPressure(){
    return this->_pressure_bar;
}

