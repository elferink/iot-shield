#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    2
#define BRIGHTNESS  16
#define LED_TYPE    APA102
#define COLOR_ORDER BGR

CRGB leds[NUM_LEDS];

#define APADATAPIN 13 // D7
#define APACLOCKPIN 14 // D5

void setRgbLeds(CRGB color);
void setRgbLed(short ledno, CRGB color);

void setupApa() {
  FastLED.addLeds<LED_TYPE, APADATAPIN, APACLOCKPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void setRgbLed(short ledno, CRGB color) {
  if(color)//dan is hij niet zwart; https://github.com/FastLED/FastLED/wiki/Pixel-reference#comparing-colors
  {
    lastColor[ledno] = color;
  }
  leds[ledno] = color;
  FastLED.show();
}

void setRgbLeds(CRGB color) {
  for (short i = 0; i < NUM_LEDS; i++) {
    setRgbLed(i, color);
  }
}

//by is tussen 0-256
void dimRgbLed(short ledno, short by) {
  leds[ledno].fadeToBlackBy( by );
}



