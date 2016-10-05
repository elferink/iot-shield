#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    2
#define BRIGHTNESS  32
#define LED_TYPE    APA102
#define COLOR_ORDER BGR

CRGB leds[NUM_LEDS];

#define APADATAPIN 13 // D7
#define APACLOCKPIN 14 // D5

void setRgbLeds(CRGB color);
void setRgbLed(int ledno, CRGB color);

void setupApa() {
  FastLED.addLeds<LED_TYPE, APADATAPIN, APACLOCKPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  setRgbLeds(CRGB::Black);
}

void setRgbLeds(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setRgbLed(i, color);
  }
}

void setRgbLed(int ledno, CRGB color) {
  leds[ledno] = color;
  FastLED.show();
}
