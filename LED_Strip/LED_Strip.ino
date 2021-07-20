#include <stdlib.h>
#include "utils.h"

#define PIN_BLUE 6
#define PIN_GREEN 5
#define PIN_RED 3

#define COL_FADE_TIME 5000

//This variable is just used for storing some state depending on the mode
uint8_t colMode;

//These hold the current colour in the random switch mode
uint8_t rCurr = 0,
        gCurr = 0,
        bCurr = 0;

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  //There are no externall pullups/pulldowns so internal pullups must be enabled
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}

void loop() {
  if (getSwitches() == 0b0000) {
    colMode = random() % 6;
    if (colMode == 0)
      fadeTo(RGB_TO_HEX(random() % 156 + 100, random() % 100, random() % 100));
    else if (colMode == 1)
      fadeTo(RGB_TO_HEX(random() % 100, random() % 156 + 100, random() % 100));
    else if (colMode == 2)
      fadeTo(RGB_TO_HEX(random() % 100, random() % 100, random() % 156 + 100));
    else if (colMode == 3)
      fadeTo(RGB_TO_HEX(random() % 156 + 100, random() % 156 + 100, random() % 100));
    else if (colMode == 4)
      fadeTo(RGB_TO_HEX(random() % 100, random() % 156 + 100, random() % 156 + 100));
  } else if (getSwitches() == 0b0001) {
    writeColour(COL_RED);
  } else if (getSwitches() == 0b0010) {
    writeColour(COL_GREEN);
  } else if (getSwitches() == 0b0011) {
    writeColour(COL_BLUE);
  } else if (getSwitches() == 0b0100) {
    if (colMode >= 3)
      colMode = 0;
    if (colMode == 0)
      fadeTo(COL_RED);
    if (colMode == 1)
      fadeTo(COL_GREEN);
    if (colMode == 2)
      fadeTo(COL_BLUE);
    colMode++;
    delay(2000);
  }
}

void writeColour(uint32_t col) {
  analogWrite(PIN_RED,   HEX_TO_RED(col));
  analogWrite(PIN_GREEN, HEX_TO_GREEN(col));
  analogWrite(PIN_BLUE,  HEX_TO_BLUE(col));
}

void fadeTo(uint32_t col) {
  uint8_t red = HEX_TO_RED(col);
  uint8_t green = HEX_TO_GREEN(col);
  uint8_t blue = HEX_TO_BLUE(col);

  //Get the number of steps that need to be traversed to reach the target colour (max of red, green or blue)
  uint8_t maxStep = max(max(abs(red - rCurr), abs(green - gCurr)), abs(blue - bCurr));
  uint8_t del = COL_FADE_TIME / maxStep;

  //Loop while we haven't yet reached the target colours
  while (rCurr != red || bCurr != blue || gCurr != green) {
    //For each colour, move a step closer to the target
    if (rCurr < red)
      rCurr++;
    else if (rCurr > red)
      rCurr--;

    if (gCurr < green)
      gCurr++;
    else if (gCurr > green)
      gCurr--;

    if (bCurr < blue)
      bCurr++;
    else if (bCurr > blue)
      bCurr--;

    //Write the new colour to the strip
    analogWrite(PIN_RED, rCurr);
    analogWrite(PIN_GREEN, gCurr);
    analogWrite(PIN_BLUE, bCurr);
    delay(del);
  }
}

uint8_t getSwitches() {
  return (digitalRead(12))
         | (digitalRead(11) << 1)
         | (digitalRead(10) << 2)
         | (digitalRead(9) << 3);
}