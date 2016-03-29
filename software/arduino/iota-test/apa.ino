#include <APA102.h>

#define APADATAPIN 13 // D7
#define APACLOCKPIN 14 // D5

const uint8_t brightness = 31;
const uint16_t ledCount = 2;

APA102<APADATAPIN, APACLOCKPIN> strip;
rgb_color colors[ledCount];

boolean apa_on = false;

void setupApa() {
  apaAllOff();
}

void apaAllOff() {
  for (int i = 0; i < ledCount; i++) {
    colors[i] = rgb_color{0, 0, 0};
  }
  strip.write(colors, ledCount, brightness);
}

void apaOff() {
  apaAllOff();
}

void loopApa()
{
  if (apa_on) {
    uint8_t time = millis() >> 2;
    for (uint16_t i = 0; i < ledCount; i++)
    {
      uint8_t x = time - i * 8;
      colors[i].red = x;
      colors[i].green = 255 - x;
      colors[i].blue = x;
    }

    strip.write(colors, ledCount, brightness);

    delay(10);
  }
}

