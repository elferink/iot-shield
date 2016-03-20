#include <APA102.h>

#define APADATAPIN 13 // D7
#define APACLOCKPIN 14 // D5

const uint8_t brightness = 31;
const uint16_t ledCount = 2;

APA102<APADATAPIN, APACLOCKPIN> strip;
rgb_color colors[ledCount];

void setupApa() {
  for (int i = 0; i < ledCount; i++) {
      colors[i] = rgb_color{0,0,0};      
  }
  strip.write(colors, ledCount, brightness);
}

void setLed(int ledno, int r, int g, int b) {
  colors[ledno].red = r;
  colors[ledno].green = g;
  colors[ledno].blue = b;
  strip.write(colors, ledCount, brightness);
}

void setLeds(int r, int g, int b) {
  for (int i = 0; i < ledCount; i++) {
    colors[i].red = r;
    colors[i].green = g;
    colors[i].blue = b;
  }
  strip.write(colors, ledCount, brightness);
}

