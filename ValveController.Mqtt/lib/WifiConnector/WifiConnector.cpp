/*
    WifiConnector.h - Library for connecting to a local wireless network
    Created by Robert Hoffmann, 2022
*/

#include "WifiConnector.h"

WifiConnector::WifiConnector(){

}

void connect(char* ssid, char* password) {
  delay(50);
  Serial.println();
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
}


void WifiConnector::ensureConnection(char* ssid, char* password) {
  unsigned long currentMillis = millis();
  if(currentMillis - PreviousMillis >= Interval) {
    if(WiFi.status()== WL_CONNECTED ) {
      if(Online == 0) {// was disconnected, now connected
        Serial.println("Wifi connection established");
        Online = 1;
      }
    } else{
      if(Online == 1){ //was Online, now disconnected
        Serial.println("Wifi connection lost");
        Online = 0;
      }
      Serial.println("Trying to Reconnect to Wifi.");
      while(WiFi.status() != WL_CONNECTED) {
        connect(ssid,password);
        delay(500);
        Serial.print("Reconnecting...");
      }
    }
     PreviousMillis = currentMillis;
  }
}

