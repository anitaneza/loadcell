#include "wifiManager.h"

void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("Gagal mount SPIFFS");
  } else {
    Serial.println("Sukses mount SPIFFS");
  }
}

void writeFile(fs::FS &fs, const char* path, const char* message) {
  Serial.printf("Menulis file: %s\n", path);

  File file = fs.open(path, "w");
  if (!file) {
    Serial.println("Gagal membuka file untuk menulis");
    return;
  }

  if (file.print(message)) {
    Serial.println("File berhasil ditulis");
  } else {
    Serial.println("Gagal menulis ke file");
  }

  file.close();
}

String readFile(fs::FS &fs, const char* path) {
  Serial.printf("Membaca file: %s\n", path);

  if (!fs.exists(path)) {
    Serial.printf("File %s tidak ditemukan\n", path);
    return "";
  }

  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    Serial.printf("Gagal membuka file: %s\n", path);
    return "";
  }

  String fileContent = file.readStringUntil('\n');
  file.close();
  return fileContent;
}

// Mengecek username dan password
bool checkLogin(String inputUser, String inputPass) {
  String loginData = readFile(SPIFFS, "/login.txt");

  if (loginData == "") return false;

  int delimiterIndex = loginData.indexOf(';');
  if (delimiterIndex == -1) return false;

  String storedUser = loginData.substring(0, delimiterIndex);
  String storedPass = loginData.substring(delimiterIndex + 1);

  return (storedUser == inputUser && storedPass == inputPass);
}

// Menyimpan username dan password ke file
void saveLogin(String username, String password) {
  String loginData = username + ";" + password;
  writeFile(SPIFFS, "/login.txt", loginData.c_str());
}
