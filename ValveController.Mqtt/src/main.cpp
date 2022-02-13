#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <credentials.h>
#include <ota.h>
#include <WifiConnector.h>
#include <MqttConnector.h>
#include <ValveController.h>
#include <PressureChecker.h>

const char* Ssid = mySSID;
const char* Password = myPASSWORD;
const char* nameforClient = "ValveController1";

long currentTime, lastTime;

MqttConnector mqtt(nameforClient, myMqttBrokerIP, myMqttBrokerPort);
WifiConnector wifi;
const int numberOfValves = 8;
const int valvePins[numberOfValves] = {25,18,14,33,26,13,27,32};
ValveController valve(numberOfValves); 
PressureChecker pressureChecker(34, 2.0, 5);
#define ONBOARD_LED  2


void setup() {
  SetupOTA(nameforClient, Ssid, Password);
  pinMode(ONBOARD_LED,OUTPUT);
  Serial.begin(115200);
  
  pressureChecker.AddEventHandler(&mqtt);

  valve.initialisePins(valvePins);

  setInterval(60); // every minute ntp update
  waitForSync();
}


void loop() {
  ArduinoOTA.handle();
  wifi.ensureConnection(mySSID, myPASSWORD);
  mqtt.CheckConnection();
  valve.checkEvents(valvePins);
  // actionScheduler.CheckDueDates();
  pressureChecker.CheckPressure();
}

