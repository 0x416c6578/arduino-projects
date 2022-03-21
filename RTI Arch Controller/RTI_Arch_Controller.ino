#define dirPin 13 //Direction pin - high = anticlockwise
#define MOVE_ANTICLOCKWISE HIGH
#define MOVE_CLOCKWISE LOW
#define stepPin A0
#define homeSwitch 12

#define MOVE_SUCCESS 0
#define MOVE_FAILURE 1

bool homed = 0;
unsigned char pos = 0;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, MOVE_CLOCKWISE);

  pinMode(homeSwitch, INPUT_PULLUP);

  homeSequence();
}

void loop() { }

/**
 * Home the arch
 */
void homeSequence() {
  digitalWrite(dirPin, HIGH); //Set correct direction

  //If we are already homed
  if (digitalRead(homeSwitch) == 0)
    homed = 1;

  //Otherwise move until we are homed
  while (homed == 0) {
    if (digitalRead(homeSwitch) == 0) {
      homed = 1;
    }
    for(int i = 0; i < 32; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  }
  pos = 0;
  return;
}

/**
 * Move to a position (in degrees)
 */
bool moveTo(unsigned char newPos) {
  if (newPos < 0 || newPos > 180 || homed == 0)
    return MOVE_FAILURE;

  if (newPos == pos)
    return MOVE_SUCCESS;

  bool dirToMove = newPos < pos ? MOVE_ANTICLOCKWISE : MOVE_CLOCKWISE;
  digitalWrite(dirPin, dirToMove);

  while (pos != newPos) {
    //Move one degree (1/32 microstep; 200 steps/revolution on servo means 1.8 deg/step on
    //servo. 1:9 timing pulley reduction leads to 0.2 arch degrees/step; so there are
    //32*5 pulses/degree
    for (int i = 0; i < 32*5; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
    //Until we reach the desired position
    pos += dirToMove == MOVE_ANTICLOCKWISE ? -1 : 1;
  }

  return MOVE_SUCCESS;
}

/**
 * Debug / test function to scan slowly accross all LEDs
 */
void ledScan() {
  digitalWrite(11,LOW);
  digitalWrite(2,HIGH);
  delay(300);
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  delay(300);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  delay(300);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  delay(300);
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  delay(300);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  delay(300);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  delay(300);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  delay(300);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  delay(300);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  delay(300);
  digitalWrite(11,LOW);
}