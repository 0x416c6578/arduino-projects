#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "secret.h"
#include "index.h"

Servo x;
Servo y;

ESP8266WebServer server;

//Handler for /setPos request
void setPos() {
  String posX = server.arg("x");
  String posY = server.arg("y");
  x.write(posX.toInt());
  y.write(posY.toInt());
  delay(15);
  server.send(200, "text/plane", "");
}

//Hander for /home request
void home() {
  x.write(90);
  y.write(90);
  delay(15);
  server.send(200, "text/plane", "");
}

//Handler for / request
void root() {
  String res = page;
  server.send(200, "text/html", res);
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

  server.on("/setPos", setPos);
  server.on("/home", home);
  server.on("/", root);
  server.begin();
}

void loop() {
  server.handleClient();
}