#define LEDPIN 2 // D4

void setupLed() {
  pinMode(LEDPIN, OUTPUT);
  ledOff();
}

void setLed(bool state) {
  if (state == HIGH) {
    digitalWrite(LEDPIN, LOW);
  } else {
    digitalWrite(LEDPIN, HIGH);
  }
}

void ledOn() {
  setLed(HIGH);
}

void ledOff() {
  setLed(LOW);
}

