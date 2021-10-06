void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  //Rough timings based on calculations in info page
  for(int i = 0; i < 14; i++) {
    digitalWrite(13, HIGH);
    delay(33);
    digitalWrite(13, LOW);
    delay(33);
  }
  digitalWrite(13, HIGH);
  delay(16);
  digitalWrite(13, LOW);
  delay(49);
}
