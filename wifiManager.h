#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include "configuration.h"
#include "SPIFFS.h"

    void initSPIFFS();
    void writeFile(fs::FS &fs, const char * path, const char * message);
    String readFile(fs::FS &fs, const char * path);

    bool checkLogin(String inputUser, String inputPass);
    void saveLogin(String username, String password);

#endif
