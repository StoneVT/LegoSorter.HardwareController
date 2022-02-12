/*
    MqttConnector.h - Library for connecting to a local mqtt service
    Created by Robert Hoffmann, 2022
*/
#ifndef MqttConnector_h
#define MqttConnector_h

#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

class MqttConnector{  
private:
    PubSubClient* _client;
    const char* _clientName;
public:
    MqttConnector(PubSubClient& client, const char* clientName);
    PubSubClient& setClient(PubSubClient& client);
    const char* setClientName(const char* clientName);
    void resubscribe(const char* inTopic);
};


#endif