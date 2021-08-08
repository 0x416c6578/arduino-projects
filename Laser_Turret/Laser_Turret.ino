#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "secret.h"

Servo x;
Servo y;

ESP8266WebServer server;

//Callback function for /setPos request
void servoPost() {
  String posX = server.arg("x");
  String posY = server.arg("y");
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
  WiFi.setHostname("laser");

  bool ledState = false;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED_BUILTIN, ledState);
    ledState = !ledState;
  }

  //We have connected; set LED high
  digitalWrite(ledState, 1);

  server.on("/setPos", servoPost);
  server.begin();
}

void loop() {
  server.handleClient();
}