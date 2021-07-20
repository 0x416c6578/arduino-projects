#include <TFT_eSPI.h>
#include <SPI.h>
#include "WiFi.h"

TFT_eSPI tft = TFT_eSPI(135,240);
char buff[512];

void setup() {
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_WHITE);
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLACK);

  WiFi.setHostname("ESP32");
  WiFi.mode(WIFI_STA);
  WiFi.begin("BT-Home", "3MpDHpFMHNgHcD");
  while (WiFi.status() != WL_CONNECTED) {
    tft.drawString("Connecting", 0, 0);
    delay(1000);
  }
  tft.fillScreen(TFT_WHITE);
  tft.drawString(WiFi.localIP().toString(), 0, 0);


}

void loop() {
}