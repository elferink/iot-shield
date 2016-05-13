#include "OneButton.h"

#define BUTTONPIN 0 // D3

OneButton button(BUTTONPIN, true);

void setupButton() {
  pinMode(BUTTONPIN, INPUT);
  
  button.setClickTicks(300);
  button.setPressTicks(600);

  button.attachClick(singleClick);
  button.attachDoubleClick(doubleClick);
  button.attachLongPressStart(longPress);
}

void singleClick() {
  if (!apa_on && !led_on) {
    ledOn();
  } else if (led_on) {
    ledOff();
    apaOn();
  } else if (apa_on) {
    apaOff();
  }
}

void doubleClick() {
  nextPattern();
}

void longPress() {
  report();
}

void loopButton() {
  button.tick();
}


