#define BUTTONPIN 0 // D3

int lastPush = 0;
int debounceDelay = 1000; // 1 second

int pushed = 0;

void setupButton() {
  pinMode(BUTTONPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), buttonPressed, FALLING);
}

void buttonPressed() {
  int state = digitalRead(BUTTONPIN);
  if (state == LOW && ((millis() - lastPush) > debounceDelay)) {
    lastPush = millis();
    // no other actions while handling interrupt 
    pushed = 1;
  }
}

void loopButton() {
  if (pushed) {
    Serial.println("Button pushed");
    if (!apa_on && !led_on) {
      led_on = true;
      ledOn();
    } else if (led_on) {
      led_on = false;
      ledOff();

      apa_on = true;
    } else if (apa_on) {
      apa_on = false;
      apaOff();
    }
    
    pushed = 0;
  }
}


