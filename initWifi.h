#ifndef INITWIFI_H
#define INITWIFI_H

#include "configuration.h"
#include "wifiManager.h"

class setWifi{
  public:
   bool initWifi();
   void reconnectWifi();

  private:
   unsigned long currentMillis;
   unsigned long previousMillis = 0;
   const long interval = 10000;
};

#endif
