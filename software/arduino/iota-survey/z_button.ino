#include "OneButton.h"

#define BUTTONPIN 0 // D3

OneButton button(BUTTONPIN, true);

void singleClick();

void setupButton() {
  pinMode(BUTTONPIN, INPUT);

  button.setClickTicks(300);
  button.setPressTicks(600);

  button.attachClick(singleClick);
}

void singleClick() {
  if (enabled && !fade_apa && !blink_apa && millis() > back_on_time) {
    // cast vote
    char vote[50];
    sprintf(vote, "%s %s", survey_node_id, vote_value);
    client.publish(vote_topic, vote);
  }
}

void loopButton() {
  button.tick();
}


