#define BUTTONPIN 0 // D3

int lastPush = 0;
int debounceDelay = 1000; // 1 second

int publish = 0;

void setupButton() {
  pinMode(BUTTONPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), buttonPressed, FALLING);
}

void buttonPressed() {
  int state = digitalRead(BUTTONPIN);
  if (state == LOW && ((millis() - lastPush) > debounceDelay)) {
    lastPush = millis();
    // no other actions while handling interrupt 
    publish = 1;
  }
}

void loopButton() {
  if (publish) {
    Serial.println("Button pushed");
    pub("button", "ON");
    publish = 0;
  }
}

