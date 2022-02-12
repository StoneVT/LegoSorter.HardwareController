/*
    ValveController.h - Library for controlling connected Valves and opening them on given times
    Created by Robert Hoffmann, 2022
*/

#ifndef ValveController_h
#define ValveController_h

#include <Arduino.h>
#include <CircularBuffer.h>
#include <ezTime.h>
#include <TimestampModifier.h>
#include <string>
#include <vector>

class ValveController{
    typedef struct {
    long pushtime;
    bool openValve;
    int bucket;
    char* guid;
    char* partno;
    int colorid;
    } BrickAction;

private:
    int _numberOfValves;
    CircularBuffer<BrickAction,20> _buffer[8];
    TimestampModifier time;
    void changeValvePosition(const int valvePins[], int valvenumber, bool openValve);
    void setNumberOfValves(int numberOfValves);

public:
    ValveController(int numberOfValves);
    void checkEvents(const int valvePins[]);
    void addEvent(char* payload);
};

#endif