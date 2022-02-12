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
  Serial.print("\n[WIFI]\tConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("[WIFI]\tconnected.");
  Serial.println("[WIFI]\tIP address: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
}


void WifiConnector::ensureConnection(char* ssid, char* password) {
  unsigned long currentMillis = millis();
  if(currentMillis - _previousMillis >= _interval) {
    if(WiFi.status()== WL_CONNECTED ) {
      if(_online == 0) {// was disconnected, now connected
        Serial.println("[WIFI]\tConnection established");
        _online = 1;
      }
    } else{
      if(_online == 1){ //was Online, now disconnected
        Serial.println("[WIFI]\tConnection lost");
        _online = 0;
      }
      Serial.println("[WIFI]\tTrying to Reconnect");
      while(WiFi.status() != WL_CONNECTED) {
        connect(ssid,password);
        delay(500);
        Serial.print("[WIFI]\tReconnecting...");
      }
    }
     _previousMillis = currentMillis;
  }
}


wl_status_t WifiConnector::status(){
    return WiFi.status();
}

