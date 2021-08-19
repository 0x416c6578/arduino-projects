#include <RH_ASK.h>
#include <SPI.h>

#define BUF_LEN 50

RH_ASK driver;
uint8_t buf[BUF_LEN];
uint8_t buflen;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  if (!driver.init()) {
    digitalWrite(LED_BUILTIN, HIGH);
    for (;;) {}
  }
}

void loop() {
  buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    //Print the message followed by the size of that received message
    Serial.print((char*) buf);
    Serial.print(" [");
    Serial.print(buflen);
    Serial.println("]");
  }
}