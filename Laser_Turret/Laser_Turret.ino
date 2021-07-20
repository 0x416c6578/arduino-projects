#include <Servo.h>

Servo x;
Servo y;

void setup() {
  x.attach(D0);
  y.attach(D1);

  x.write(90);
  y.write(90);

}

void loop() {}
