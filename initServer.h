#ifndef INITSERVER_H
#define INITSERVER_H

#include "configuration.h"
#include "wifiManager.h"
#include <ESPAsyncWebServer.h>

extern AsyncWebServer server1;

void serverRoute();
void handleConfig();
void apMode();

#endif
