#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <credentials.h>
#include <ota.h>
#include <WifiConnector.h>
#include <MqttConnector.h>
#include <ValveController.h>

const char* Ssid = mySSID;
const char* Password = myPASSWORD;
const char* MqttBrokerIP = myMqttBrokerIP;
const uint_fast16_t MqttBrokerPort = myMqttBrokerPort;
const char* nameforClient = "ValveController1";
const char* outTopic = "valvecontroller/1/status"; 
const char* pushBrickTopic = "pushbrick";

long currentTime, lastTime;

WiFiClient espClient;
PubSubClient client(espClient);
WifiConnector wifi;
MqttConnector mqtt(client, nameforClient);
const int numberOfValves = 8;
const int valvePins[numberOfValves] = {25,18,14,33,26,13,27,32};
ValveController valve(numberOfValves); 


#define ONBOARD_LED  2
char* msg;

void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("Received [" + String(topic) + "] message.");
  payload[length] = '\0';
  if (strcmp(topic, pushBrickTopic) == 0) { 
    valve.addEvent((char*)payload);
  }

}

void setup() {
  SetupOTA(nameforClient, Ssid, Password);
  pinMode(ONBOARD_LED,OUTPUT);
  Serial.begin(115200);
  client.setServer(MqttBrokerIP, MqttBrokerPort);
  client.setCallback(callback);
}

void loop() {
  wifi.ensureConnection(mySSID, myPASSWORD);
  if(!client.connected()){
    mqtt.resubscribe(pushBrickTopic);
  }
  client.loop();
  //valve.checkEvents(valvePins);
  //delay(2000);
  //client.publish(outTopic, "alive");
}