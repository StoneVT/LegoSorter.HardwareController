/*
    MqttConnector.h - Library for connecting to a local mqtt service
    Created by Robert Hoffmann, 2022
*/
#include "MqttConnector.h"

#include <Arduino.h>
#include <ezTime.h>

#include <TimestampModifier.h>

#include <sstream>

MqttConnector::MqttConnector(const char* clientName, const char* ip, const uint_fast16_t port){
    setClientName(clientName);
    WiFiClient wc;
    _client = PubSubClient(wc);
    _client.setServer(ip, port);
    _client.setCallback(callback);
    _client.publish(statusTopic_, "online");
}

void MqttConnector::callback(char* topic, byte* payload, unsigned int length)
  {
      Serial.println("[MQTT]\tReceived [" + String(topic) + "] message.");
      // payload[length] = '\0';
      // if (strcmp(topic, pushBrickTopic_) == 0) { 
      // valve.addEvent((char*)payload);
      // }
      // TODO: Fire MessageReceivedEvent
   }

void MqttConnector::CheckConnection() {
  if(!_client.connected()){
    this->resubscribe(pushBrickTopic_);
    waitForSync();
    Timezone myLocalTime;
    myLocalTime.setLocation(F("de")); // set your time zone
    TimestampModifier timestampModifier;
    Serial.println("[TIME]\tNTP Update received. Current time is " + myLocalTime.dateTime("d.m.Y H:i:s.v T") + "|" +  timestampModifier.getUnixTimeStamp());
  }
}

void MqttConnector::resubscribe(const char* inTopic){
  while(!_client.connected()){
      Serial.println("[MQTT]\tConnecting as " + String(_clientName) + "...");
    if(_client.connect(_clientName,"","")){
      Serial.println("[MQTT]\tConnected as " + String(_clientName));
      _client.subscribe(inTopic, 1);
    } else {
      Serial.println("\n[MQTT]\tTrying to resubscribe again.");
      delay(5000);
    }
  }
}

const char* MqttConnector::setClientName(const char* clientName){
    this->_clientName = clientName;
    return clientName;
}

void MqttConnector::HandleEvent(event::Event* e) {
  switch(e->GetType()){
    case event::Type::pressureCritical:
      {
        auto* pce = static_cast<event::PressureCriticalEvent*>(e);
        std::stringstream ss;
        ss << "Pressure level critical! Threshold: " << pce->Threshold() << " Current pressure: " << pce->Pressure_bar() << std::endl;
        _client.publish(statusTopic_, ss.str().c_str());
      }      
      break;
    default:
      break;
  }
}

