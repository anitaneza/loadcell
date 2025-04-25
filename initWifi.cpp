#include "initWifi.h"

bool setWifi::initWifi(){
  if(ssid == "" || ip == ""){
    Serial.println("ssid atau ip tidak ditemukan");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());

//  if (!WiFi.config(localIP, localGateway, subnet, primaryDNS, secondaryDNS)) {
//    Serial.println("STA Failed to configure");
//    return false;
//  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  currentMillis = millis();
  previousMillis = currentMillis;
  
  while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }
  Serial.println(WiFi.localIP());
  return true;
}

void setWifi::reconnectWifi(){
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    
    currentMillis = millis();
    previousMillis = currentMillis;
    
   while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
//      Serial.println("Failed to connect.");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nReconnected to WiFi!");
    } else {
//      Serial.println("\nFailed to reconnect.");
    }
  }
 }
}
