#include "displayManager.h"

displayManager::displayManager(int lcd_addr, int screen_width, int screen_height)
  : lcd(screen_width, screen_height, &Wire), screenWidth(screen_width), screenHeight(screen_height),
    tempDisplayStart(0), tempDisplayDuration(0), showingTempMessage(false) {}

void displayManager::begin() {
  if (!lcd.begin(SSD1306_SWITCHCAPVCC, lcd_addr)) {
    Serial.println("Gagal inisialisasi OLED!");
    while (1);
  }
  lcd.setTextColor(SSD1306_WHITE);
  lcd.clearDisplay();
  lcd.setTextSize(1);
  lcd.setCursor(0, 0);
  lcd.println("Ready...");
  lcd.display();
}

void displayManager::setScalePtr(digitalScale* scale) {
  scalePtr = scale;
}

void displayManager::displayMessage(String line1, String line2, int duration) {
  Serial.println("Menampilkan pesan di OLED: " + line1 + (line2 != "" ? " | " + line2 : ""));
  lcd.clearDisplay();
  lcd.setTextSize(1);
  lcd.setTextColor(SSD1306_WHITE);

  // Tengah horizontal untuk baris 1
  int16_t x = (screenWidth - (line1.length() * 6)) / 2;
  if (x < 0) x = 0;
  lcd.setCursor(x, 0);
  lcd.println(line1);

  // Baris 2 (jika ada)
  if (line2 != "") {
    x = (screenWidth - (line2.length() * 6)) / 2;
    if (x < 0) x = 0;
    lcd.setCursor(x, 16);
    lcd.println(line2);
  }
  lcd.display();
  
  if (duration > 0) {
    showingTempMessage = true;
    tempMessageLine1 = line1;
    tempMessageLine2 = line2;
    tempDisplayStart = millis();
    tempDisplayDuration = duration;
  } else {
    showingTempMessage = false;
  }
}

void displayManager::displayPingSuccess(String device_id) {
  displayMessage("Ping berhasil", device_id, 3000);
}

void displayManager::displayDataSent() {
  displayMessage("Data dikirim", "", 1000);
}

void displayManager::updateDisplay() {
  if (showingTempMessage) {
    if (millis() - tempDisplayStart >= tempDisplayDuration) {
      showingTempMessage = false;
      Serial.println("Pesan sementara selesai, kembali ke data sensor");
    } else {
      return;
    }
  }

  if (scalePtr) {
    float berat = scalePtr->readScale();
    String beratStr = String(berat, 0) + " Gram"; // Format: "X.XX Gram" (berat,2)
    
    lcd.clearDisplay();
    lcd.setTextColor(SSD1306_WHITE);

    // Baris 1: "Berat:" (kiri atas, textSize 1)
    lcd.setTextSize(1);
    String label = "Berat:";
    lcd.setCursor(0, 0);
    lcd.println(label);

    // Baris 2: "X.XX Gram" (tengah horizontal dan vertikal, textSize 2)
    lcd.setTextSize(2);
    int16_t textWidth = beratStr.length() * 12; // 12 piksel per karakter
    int16_t textHeight = 16; // Tinggi font untuk textSize(2)
    int16_t x = (screenWidth - textWidth) / 2; // Tengah horizontal
    int16_t y = (screenHeight - textHeight) / 2; // Tengah vertikal
    if (x < 0) x = 0;
    lcd.setCursor(x, y);
    lcd.println(beratStr);

    lcd.display();
  }
}
