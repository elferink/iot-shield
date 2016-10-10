#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    2
#define BRIGHTNESS  15
#define LED_TYPE    APA102
#define COLOR_ORDER BGR

CRGB leds[NUM_LEDS];

#define APADATAPIN 13 // D7
#define APACLOCKPIN 14 // D5

void setRgbLeds(CRGB color);
void setRgbLed(int ledno, CRGB color);

boolean fade_apa_down = true;
bool pressed = false;

void setupApa() {
  FastLED.addLeds<LED_TYPE, APADATAPIN, APACLOCKPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loopApa() {
  if (pressed) {
    EVERY_N_MILLISECONDS(150) {
      if (fade_apa_down) {
        dimRgbLed(0,192);
      } else {
        setRgbLed(0, CRGB::Green);
      }
      fade_apa_down  = !fade_apa_down;
      FastLED.show();
    }
  } 
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

void dimRgbLed(short ledno, short by) {
  leds[ledno].fadeToBlackBy( by );
}
