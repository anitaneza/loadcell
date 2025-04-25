#include "buttonHandler.h"
#include <ArduinoJson.h>
#include "configuration.h"

buttonHandler::buttonHandler(int pin) : buttonPin(pin), lastButtonState(HIGH) {}

void buttonHandler::begin() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("ButtonHandler diinisialisasi pada pin " + String(buttonPin));
}

void buttonHandler::setMqttPtr(mqttClient* mqtt) {
  mqttPtr = mqtt;
}

void buttonHandler::setDisplayPtr(displayManager* display) {
  displayPtr = display;
}

void buttonHandler::handleButton() {
  bool reading = digitalRead(buttonPin);
//  Serial.print("Button reading: ");
//  Serial.print(reading);
//  Serial.print(" | lastButtonState: ");
//  Serial.println(lastButtonState);

  if (reading == LOW && lastButtonState == HIGH) {
    Serial.println("Tombol ping ditekan, mengirim pesan...");
    
    StaticJsonDocument<128> doc;
    doc["message"] = "ping";
    char jsonBuffer[128];
    serializeJson(doc, jsonBuffer);
    
    if (mqttPtr) {
      mqttPtr->sendData(jsonBuffer, mqtt_topic);
      Serial.println("Pesan JSON dikirim: " + String(jsonBuffer));
      if (displayPtr) {
        displayPtr->displayMessage("Ping dikirim...", "", 1000);
      }
    } else {
      Serial.println("mqttPtr belum diset!");
    }
  }
  
  lastButtonState = reading;
}
