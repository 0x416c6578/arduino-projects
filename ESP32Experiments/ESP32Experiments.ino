#include <TFT_eSPI.h>
#include <SPI.h>
#include "HTTPClient.h"
#include "WiFi.h"

#define HTTP_PORT 8080
#define HTTP_METHOD "GET"
#define HOSTNAME "pi-3b"

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
  WiFi.begin(SSID, PSK);

  tft.setCursor(0,0);
  tft.println("Connecting...");
  tft.setCursor(0,0);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  tft.fillScreen(TFT_WHITE);
  tft.println(WiFi.localIP().toString());

  HTTPClient client;

  tft.setTextSize(3);
  client.begin(HOSTNAME, HTTP_PORT);
  int code = client.GET();
  String payload = client.getString();
  // tft.printf("%04d\n", code);
  tft.println();
  tft.println(payload);
}


void loop() {
}