#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  if (!driver.init())
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  const char *msg = "Hello World!";
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}
