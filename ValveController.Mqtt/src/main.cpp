#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <credentials.h>
#include <ota.h>
#include <WifiConnector.h>
#include <MqttConnector.h>
#include <ValveController.h>
#include <ezTime.h>
#include <TimestampModifier.h>
#include <PressureChecker.h>

const char* Ssid = mySSID;
const char* Password = myPASSWORD;
const char* MqttBrokerIP = myMqttBrokerIP;
const uint_fast16_t MqttBrokerPort = myMqttBrokerPort;
const char* nameforClient = "ValveController1";
const char* statusTopic = "valvecontroller/1/status"; 
const char* pushBrickTopic = "pushbrick";

long currentTime, lastTime;

//TODO: Move WiFiClient and PubSubClient to MqttConnector library
WiFiClient espClient;
PubSubClient client(espClient);
MqttConnector mqtt(client, nameforClient);
WifiConnector wifi;
const int numberOfValves = 8;
const int valvePins[numberOfValves] = {25,18,14,33,26,13,27,32};
ValveController valve(numberOfValves); 
Timezone myLocalTime;
TimestampModifier timestampModifier;
PressureChecker pressure;
#define ONBOARD_LED  2

void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("[MQTT]\tReceived [" + String(topic) + "] message.");
  payload[length] = '\0';
  if (strcmp(topic, pushBrickTopic) == 0) { 
    valve.addEvent((char*)payload);
  }
}

void setup() {
  SetupOTA(nameforClient, Ssid, Password);
  pinMode(ONBOARD_LED,OUTPUT);
  myLocalTime.setLocation(F("de")); // set your time zone
  Serial.begin(115200);
  
  //TODO: Move WiFiClient and PubSubClient to MqttConnector library
  client.setServer(MqttBrokerIP, MqttBrokerPort);
  client.setCallback(callback);

  valve.initialisePins(valvePins);

  setInterval(60); // every minute ntp update
  waitForSync();
  client.publish(statusTopic, "online");
}

void checkInit(){
  wifi.ensureConnection(mySSID, myPASSWORD);
  if(!client.connected()){
    mqtt.resubscribe(pushBrickTopic);
    waitForSync();
    Serial.println("[TIME]\tNTP Update received. Current time is " + myLocalTime.dateTime("d.m.Y H:i:s.v T") + "|" +  timestampModifier.getUnixTimeStamp());
  }
}

//TODO: How to get isCritical as bool?
void checkPressure(){
  /*if (pressure.isCritical() == 1)
  {
    float pressure = pressure.getPressure();
    //TODO: How to define the string so is is sendable with pressure reading?
    char* message = "low pressure!"; //  + pressure + " bar"; 
    client.publish(statusTopic,"low pressure!");
  }
  */
}

void loop() {
  ArduinoOTA.handle();
  checkInit();
  client.loop();
  valve.checkEvents(valvePins);
  checkPressure();
}

