/*
    WifiConnector.h - Library for connecting to a local wireless network
    Created by Robert Hoffmann, 2022
*/
#ifndef WifiConnector_h
#define WifiConnector_h

#include <Arduino.h>
#include <WiFi.h>

class WifiConnector{
    bool Online = 0;
    unsigned long PreviousMillis = 0;
    const long Interval = 2000; 
    public:
        WifiConnector();
        void ensureConnection(char* ssid, char* password);
};


#endif