#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "secret.h"

Servo x;
Servo y;

ESP8266WebServer server;

void servoPost() {
  String posX = server.arg("servoPosX");
  String posY = server.arg("servoPosY");
  x.write(posX.toInt());
  y.write(posY.toInt());
  delay(15);
  server.send(200, "text/plane","");
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  x.attach(D0);
  y.attach(D1);

  x.write(90);
  y.write(90);

  WiFi.begin(SSID, PSK);

  bool ledState = false;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED_BUILTIN, ledState);
    ledState = !ledState;
  }

  digitalWrite(ledState, 1);

  server.on("/set", servoPost);
  server.begin();
}

void loop() {
  server.handleClient();
}