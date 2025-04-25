#include "wifiManager.h"
#include "initWifi.h"
#include "initServer.h"
#include "mqttClient.h"
#include "digitalScale.h"
#include "buttonHandler.h"
#include "displayManager.h"
#include "configuration.h"
#include <ArduinoJson.h>

mqttClient myMQTT;
setWifi setWifi;
digitalScale scale(dout, sck, calibration_factor);
displayManager display(lcd_addr, screen_width, screen_height); // Ubah parameter
buttonHandler button(ping_button);

void setup() {
  Serial.begin(115200);

  initSPIFFS();

  if (!SPIFFS.exists("/login.txt")) {
    saveLogin("admin", "admin123");
    Serial.println("Login default disimpan (admin/admin123)");
  }

  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  ip = readFile(SPIFFS, ipPath);
  gateway = readFile(SPIFFS, gatewayPath);
  init_tare = readFile(SPIFFS, tarePath);
  scale.begin();

  Serial.println("Inisialisasi WiFi...");
  setWifi.initWifi();
  if (setWifi.initWifi()) {
    serverRoute();
    handleConfig();
  } else {
    apMode();
    serverRoute();
    handleConfig();
  }

  Serial.println("Inisialisasi perangkat...");
  display.begin();
  button.begin();
  
  myMQTT.setScalePtr(&scale);
  myMQTT.setDisplayPtr(&display);
  display.setScalePtr(&scale);
  myMQTT.reconnect();
  button.setMqttPtr(&myMQTT);
  button.setDisplayPtr(&display);
  Serial.println("Setup selesai.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    myMQTT.loop();
    button.handleButton();
  } else {
    setWifi.reconnectWifi();
    Serial.println("WiFi gagal terkoneksi (reconnect)");
  }

  display.updateDisplay();
  delay(10);
}
