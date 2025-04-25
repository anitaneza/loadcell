#include "initServer.h"

AsyncWebServer server1 (80);
    
void serverRoute() {
    // Route halaman login
    server1.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    // Route untuk login, metode POST
    server1.on("/login", HTTP_POST, [](AsyncWebServerRequest *request) {
        String inputUser, inputPass;

        if (request->hasParam("username", true) && request->hasParam("password", true)) {
            inputUser = request->getParam("username", true)->value();
            inputPass = request->getParam("password", true)->value();

            if (checkLogin(inputUser, inputPass)) {
                Serial.println("Login berhasil");
                request->redirect("/config");
            } else {
                Serial.println("Login gagal");
                request->send(200, "text/html", "<h1>Login Gagal</h1><a href='/'>Coba Lagi</a>");
            }
        } else {
            request->send(400, "text/plain", "Parameter tidak lengkap");
        }
    });

    // File-file statis lainnya
    server1.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/style.css", "text/css");
    });

    server1.on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/favicon.png", "image/png");
    });

    // Route halaman konfigurasi wifi
    server1.on("/config", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/config.html", "text/html");
    });
}

void handleConfig(){
    server1.on("/config", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        const AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(SPIFFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(SPIFFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == PARAM_INPUT_3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            // Write file to save value
            writeFile(SPIFFS, ipPath, ip.c_str());
          }
          // HTTP POST gateway value
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("Gateway set to: ");
            Serial.println(gateway);
            // Write file to save value
            writeFile(SPIFFS, gatewayPath, gateway.c_str());
          }
        }
      }
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: ");
      delay(3000);
      ESP.restart();
    });
    server1.begin(); 
}

void apMode(){
    Serial.println("Setting AP (Access Point)");
    WiFi.softAP("dev", "12345677");

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
}
