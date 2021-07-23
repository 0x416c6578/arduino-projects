#include <SPI.h>

#define CS_PIN 10
#define BYTE_COUNT 32

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  SPI.begin();

  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x03); //Read command
  SPI.transfer(0x00); //Start at address 0
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  uint8_t read;
  for (uint32_t i = 0; i < 2092152; i++) {
    read = SPI.transfer(0xff);
    //sprintf(hexBuf, "%02d", SPI.transfer(0xff));
    Serial.write(read);
  }
  digitalWrite(CS_PIN, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {

}