#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

extern WiFiClient client;

extern const char* PARAM_INPUT_1;
extern const char* PARAM_INPUT_2;
extern const char* PARAM_INPUT_3;
extern const char* PARAM_INPUT_4;

extern String ssid;
extern String pass;
extern String ip;
extern String gateway;
extern String init_tare;

extern const char* ssidPath;
extern const char* passPath;
extern const char* ipPath;
extern const char* gatewayPath;
extern const char* tarePath;

extern IPAddress localIP;
extern IPAddress localGateway;
extern IPAddress subnet;
extern IPAddress primaryDNS;
extern IPAddress secondaryDNS;

// MQTT Configuration
extern const char* mqtt_broker;
extern const char* mqtt_topic;
extern const char *mqtt_sub_topic;
extern const char* mqtt_username;
extern const char* mqtt_password;
extern const int mqtt_port;

// HX711 + button
extern const int dout;
extern const int sck;
extern const int ping_button; // Tombol ping
extern const float calibration_factor;

// OLED
extern const int lcd_addr;
extern const int screen_width;
extern const int screen_height;

#endif
