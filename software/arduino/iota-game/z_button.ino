#include "OneButton.h"

#define BUTTONPIN 0 // D3

OneButton button(BUTTONPIN, true);

void singleClick();

void setupButton() {
  pinMode(BUTTONPIN, INPUT);
  button.setClickTicks(1);
  button.attachClick(singleClick);
}

void singleClick() {
  if (game_status == STATUS_GO && pressed == false) {
    response_time = millis() - go_time;
    pressed = true;
    Serial.print("Response time: ");
    Serial.println(response_time);

    char time_subtopic[300];
    sprintf(time_subtopic, "%d/score/%s", game_number, mac);             // game/10/score/aa-bb-cc-dd-ee-ff
    pubInt(time_subtopic, response_time);
  }
}

void loopButton() {
  button.tick();
}


