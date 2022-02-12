/*
    ValveController.h - Library for controlling connected Valves and opening them on given times
    Created by Robert Hoffmann, 2022
*/
#include "ValveController.h"



ValveController::ValveController(int numberOfValves){
    setNumberOfValves(numberOfValves);
}


void ValveController::addEvent(char* payload){
    char *token = strtok(payload, ",");
    char *parameter[5];
    int i = 0;
    int duration = 20;
    while (token != NULL)
    {
        parameter[i++] = token;
        token = strtok(NULL, ",");
    };
    if (i == 5)
    {
        BrickAction action = {};
        action.bucket = int(parameter[0]);
        action.guid = parameter[1];
        action.pushtime = (long)parameter[2];
        action.partno = parameter[3];
        action.colorid = (int)parameter[4];
        action.openValve = 1;

        _buffer[action.bucket].push(action);
        action.pushtime = action.pushtime + duration;
        action.openValve = 0;
        _buffer[action.bucket].push(action);
        if(_buffer[action.bucket].isEmpty()) {
            Serial.println("Buffer is empty");
        }
/*
        Serial.println("bucket:" + String(parameter[0]));
        Serial.println("brick_guid:" + String(parameter[1]));
        Serial.println("pushtime:" + String(parameter[2]));
        Serial.println("partno:" + String(parameter[3]));
        Serial.println("colorid:" + String(parameter[4]));
        */
    }
    else
        Serial.println("Error: Invalid message. Message contained " + String(i) + " Parameters from 5 expected."); 
}

void ValveController::checkEvents(const int valvePins[]){
    for (int i = 0; i <= this->_numberOfValves-1; i++) {
    if(!this->_buffer[i].isEmpty()) {
        BrickAction currentBrickaction = this->_buffer[i].first();
        long currentTime =  time.cutTimeStampTolong(time.getUnixTimeStamp());
        Serial.println("CurrentTime:\t" + String(currentTime));
        if(currentTime - currentBrickaction.pushtime >=  0) {
            Serial.println("CurrentTime:\t" + String(currentTime) + " \t Pushtime: \t " + String(currentBrickaction.pushtime)  + "\t Bucketnumber: \t" + String(currentBrickaction.bucket)+ "\t OpenValve: \t" + String(currentBrickaction.openValve));
            Serial.println("\t Event was due before " + String(currentTime - currentBrickaction.pushtime)  + "ms");
            this->_buffer[i].shift();
            changeValvePosition(valvePins, currentBrickaction.bucket, currentBrickaction.openValve);
        } else {
            Serial.println("Bucket\t" + String(currentBrickaction.bucket)+  " will push in " + String(currentTime - currentBrickaction.pushtime)  + " ms");
        }
    }
  }
}

void ValveController::setNumberOfValves(int numberOfValves){
    this->_numberOfValves = numberOfValves;
}

void ValveController::changeValvePosition(const int valvePins[], int valvenumber, bool openValve){
  if (openValve) {
    digitalWrite(valvePins[valvenumber-1], LOW); 
    Serial.println("ValvePin " + String(valvePins[valvenumber-1]) + " was set to LOW"); 
  } else {
    digitalWrite(valvePins[valvenumber-1], HIGH); 
    Serial.println("ValvePin " + String(valvePins[valvenumber-1]) + " was set to HIGH"); 
  }
}
