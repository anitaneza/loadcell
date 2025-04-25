#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include "mqttClient.h"
#include "displayManager.h"

class buttonHandler {
private:
  int buttonPin;
  bool lastButtonState;
  mqttClient* mqttPtr;
  displayManager* displayPtr;

public:
  buttonHandler(int pin);
  void begin();
  void setMqttPtr(mqttClient* mqtt);
  void setDisplayPtr(displayManager* display); // Perbaiki
  void handleButton();
};

#endif
