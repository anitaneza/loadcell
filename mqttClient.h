#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "digitalScale.h"
#include "displayManager.h"
#include "configuration.h"

class mqttClient {
private:
  WiFiClient espClient;
  PubSubClient client;
  digitalScale* scalePtr;
  displayManager* displayPtr;

public:
  mqttClient();
  void reconnect();
  void loop();
  void sendData(const char* json, const char* topic = mqtt_sub_topic); // Tambah parameter topik
  void setScalePtr(digitalScale* scale);
  void setDisplayPtr(displayManager* display);
  void callback(char* topic, byte* payload, unsigned int length);
};

#endif
