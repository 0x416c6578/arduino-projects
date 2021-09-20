#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000);
char buf[30];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  if (!driver.init())
    digitalWrite(LED_BUILTIN, HIGH);

  driver.setModeTx();
}

void loop() {
  sprintf(buf, "RED  ");
  driver.send((uint8_t *)buf, strlen(buf));
  driver.waitPacketSent();

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  sprintf(buf, "GREEN");
  driver.send((uint8_t *)buf, strlen(buf));
  driver.waitPacketSent();

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  sprintf(buf, "BLUE ");
  driver.send((uint8_t *)buf, strlen(buf));
  driver.waitPacketSent();

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
