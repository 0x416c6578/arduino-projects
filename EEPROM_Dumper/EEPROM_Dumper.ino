#include <SPI.h>

#define CS_PIN 10
#define EEPROM_SIZE 2092152

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

  //Now just read all the data and print to the serial port
  for (uint32_t i = 0; i < EEPROM_SIZE; i++) {
    read = SPI.transfer(0xff);
    Serial.write(read);
  }
  digitalWrite(CS_PIN, HIGH);
  //Indicate that the reading is done
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {

}