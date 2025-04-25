#include "mqttClient.h"
#include "configuration.h"
#include "ArduinoJson.h"

mqttClient::mqttClient() {
  client.setClient(espClient);
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback([this](char* topic, byte* payload, unsigned int length) {
    this->callback(topic, payload, length);
  });
}

void mqttClient::reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke broker MQTT...");
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    
    Serial.printf("Terhubung dengan: %s\n", client_id.c_str());
    
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Terhubung!");
      client.subscribe(mqtt_topic);
      client.subscribe(mqtt_sub_topic);

      StaticJsonDocument<128> doc;
      doc["message"] = "ESP siap menerima pesan";
      doc["device_id"] = client_id;

      char jsonBuffer[128];
      serializeJson(doc, jsonBuffer);

      client.publish(mqtt_sub_topic, jsonBuffer);
      Serial.println("Pesan JSON dikirim saat reconnect: " + String(jsonBuffer));
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi dalam 5 detik...");
      delay(5000);
    }
  }
}

void mqttClient::loop() {
  client.loop();
}

void mqttClient::sendData(const char* json, const char* topic) {
  Serial.println("Mengirim ke MQTT, topik: " + String(topic));
  if (!client.connected()) {
    Serial.println("MQTT tidak terkoneksi, mencoba reconnect...");
    reconnect();
  }
  client.loop();
  
  bool success = client.publish(topic, json);
  if (success) {
    Serial.println("Data JSON berhasil dikirim ke MQTT: " + String(json));
    // Hanya tampilkan "Data dikirim" untuk data sensor (bukan ping)
    if (displayPtr && String(topic) == mqtt_sub_topic && strstr(json, "\"berat\"")) {
      displayPtr->displayDataSent();
    }
  } else {
    Serial.println("Gagal mengirim data JSON ke MQTT");
  }
}

void mqttClient::setScalePtr(digitalScale* scale) {
  this->scalePtr = scale;
}

void mqttClient::setDisplayPtr(displayManager* display) {
  this->displayPtr = display;
}

void mqttClient::callback(char* topic, byte* payload, unsigned int length){
  Serial.println("Callback MQTT dipanggil!");
  Serial.print("Topic: ");
  Serial.println(topic);

  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  message.trim();

  Serial.println("Topik diterima: " + String(topic));
  Serial.println("Pesan mentah: " + message);

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("Gagal parsing JSON: ");
    Serial.println(error.c_str());
    return;
  }

  const char* pesan = doc["message"];
  String device_id = String("esp32-client-") + String(WiFi.macAddress());

  Serial.print("Pesan dari JSON: ");
  Serial.println(pesan);

  if (String(topic) == mqtt_topic) {
    if (String(pesan) == "ping") {
      Serial.println("Ping diterima untuk ID: " + device_id);
      
      StaticJsonDocument<128> replyDoc;
      replyDoc["message"] = "berhasil di ping";
      replyDoc["device_id"] = device_id;

      char replyBuffer[128];
      serializeJson(replyDoc, replyBuffer);

      client.publish(mqtt_sub_topic, replyBuffer);
      Serial.println("Balasan JSON dikirim: " + String(replyBuffer));

      if (displayPtr) {
        displayPtr->displayPingSuccess(device_id);
      }
    } else if (String(pesan) == "button is pressed") {
      Serial.println("Perintah diterima, membaca berat...");
      if (scalePtr != nullptr) {
        float berat = scalePtr->readScale();
        
        StaticJsonDocument<128> doc;
        doc["berat"] = round(berat * 100) / 100.0;
        doc["device_id"] = device_id;

        char jsonBuffer[128];
        serializeJson(doc, jsonBuffer);

        client.publish(mqtt_sub_topic, jsonBuffer);
        Serial.println("Data JSON dikirim ke MQTT: " + String(jsonBuffer));
      } else {
        Serial.println("Objek timbangan belum diset");
      }
    } else {
      Serial.println("Pesan tidak dikenali");
    }
  }
}
