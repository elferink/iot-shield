#define LEDPIN 2 // D4

boolean led_on = false;

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
  led_on = true;
}

void ledOff() {
  setLed(LOW);
  led_on = false;
}

