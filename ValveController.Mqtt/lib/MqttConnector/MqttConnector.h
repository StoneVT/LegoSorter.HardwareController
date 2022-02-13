/*
    MqttConnector.h - Library for connecting to a local mqtt service
    Created by Robert Hoffmann, 2022
*/
#ifndef MqttConnector_h
#define MqttConnector_h

#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>


#include "Event.h"

class MqttConnector : public event::EventHandler {  
private:
    PubSubClient _client;
    const char* _clientName;
    const char* statusTopic_ = "valvecontroller/1/status";
    const char* pushBrickTopic_ = "pushbrick";

private:
    static void callback(char* topic, byte* payload, unsigned int length);

public:
    MqttConnector(const char* clientName, const char* ip, const uint_fast16_t port);
    const char* setClientName(const char* clientName);
    void resubscribe(const char* inTopic);

    void CheckConnection();
    void HandleEvent(event::Event* e) override;

};


#endif