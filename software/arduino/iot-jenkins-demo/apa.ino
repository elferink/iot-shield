#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    2
#define BRIGHTNESS  32
#define LED_TYPE    APA102
#define COLOR_ORDER BGR

CRGB leds[NUM_LEDS];

#define APADATAPIN 13 // D7
#define APACLOCKPIN 14 // D5

uint8_t hue = 0;
uint8_t currentPatternNumber = 0;
uint8_t color = 0;

void setupApa() {
  FastLED.addLeds<LED_TYPE, APADATAPIN, APACLOCKPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void statusColor(uint8_t status) {
  if (status == 0) {
    leds[0] = CRGB::Green;
    leds[1] = CRGB::Green;
  }
  if (status == 1) {
    leds[0] = CRGB::Red;
    leds[1] = CRGB::Red;
  }
  if (status == 2) {
    leds[0] = CRGB::Yellow;
    leds[1] = CRGB::Yellow;
  }
  if (status == 3) {
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
  }
  FastLED.show();
}
