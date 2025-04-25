#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "digitalScale.h"
#include "configuration.h"

class displayManager {
private:
  Adafruit_SSD1306 lcd;
  int screenWidth;
  int screenHeight;
  digitalScale* scalePtr;
  unsigned long tempDisplayStart;
  unsigned long tempDisplayDuration;
  bool showingTempMessage;
  String tempMessageLine1;
  String tempMessageLine2;

public:
  displayManager(int lcd_addr, int screen_width, int screen_height);
  void begin();
  void setScalePtr(digitalScale* scale);
  void displayMessage(String line1, String line2 = "", int duration = 0);
  void displayPingSuccess(String device_id);
  void displayDataSent();
  void updateDisplay();
};

#endif
