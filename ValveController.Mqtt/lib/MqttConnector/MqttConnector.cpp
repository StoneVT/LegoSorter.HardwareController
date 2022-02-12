/*
    MqttConnector.h - Library for connecting to a local mqtt service
    Created by Robert Hoffmann, 2022
*/
#include "MqttConnector.h"

MqttConnector::MqttConnector(PubSubClient& client, const char* clientName){
    setClient(client);
    setClientName(clientName);
}

void MqttConnector::resubscribe(const char* inTopic){
  while(!_client->connected()){
      Serial.println("[MQTT]\tConnecting as " + String(_clientName) + "...");
    if(_client->connect(_clientName,"","")){
      Serial.println("[MQTT]\tConnected as " + String(_clientName));
      _client->subscribe(inTopic, 1);
    } else {
      Serial.println("\n[MQTT]\tTrying to resubscribe again.");
      delay(5000);
    }
  }
}

PubSubClient& MqttConnector::setClient(PubSubClient& client){
    this->_client = &client;
    return client;
}

const char* MqttConnector::setClientName(const char* clientName){
    this->_clientName = clientName;
    return clientName;
}

