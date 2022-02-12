/*
    WifiConnector.h - Library for connecting to a local wireless network
    Created by Robert Hoffmann, 2022
*/
#ifndef WifiConnector_h
#define WifiConnector_h

#include <Arduino.h>
#include <WiFi.h>

class WifiConnector{
private:
    bool _online = 0;
    unsigned long _previousMillis = 0;
    const long _interval = 2000; 
public:
    WifiConnector();
    wl_status_t status();
    void ensureConnection(char* ssid, char* password);
};


#endif