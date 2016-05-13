#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    2
#define BRIGHTNESS  32
#define LED_TYPE    APA102
#define COLOR_ORDER BGR

CRGB leds[NUM_LEDS];

#define APADATAPIN 13 // D7
#define APACLOCKPIN 14 // D5

boolean apa_on = false;

uint8_t hue = 0;
uint8_t currentPatternNumber = 0;
uint8_t color = 0;

typedef void (*SimplePatternList[])();
SimplePatternList patterns = { rgb, rainbow };

void setupApa() {
  FastLED.addLeds<LED_TYPE, APADATAPIN, APACLOCKPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  apaOff();
}

void apaOff() {
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  FastLED.show();
  apa_on = false;
}

void apaOn() {
  apa_on = true;
}

void loopApa()
{
  if (apa_on) {
    patterns[currentPatternNumber]();
    FastLED.show();
    EVERY_N_MILLISECONDS( 20 ) { hue++; }
    EVERY_N_MILLISECONDS( 1000 ) { 
        color = color + 1;
        if (color > 2) {
          color = 0;
        }
      }
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  currentPatternNumber = (currentPatternNumber + 1) % ARRAY_SIZE( patterns);
}

void rainbow() 
{
  fill_rainbow( leds, NUM_LEDS, hue, 7);
}

void rgb() {
  if (color == 0) {
    leds[0] = CRGB::Red;
    leds[1] = CRGB::Red;
  }

  if (color == 1) {
    leds[0] = CRGB::Green;
    leds[1] = CRGB::Green;
  }

  if (color == 2) {
    leds[0] = CRGB::Blue;
    leds[1] = CRGB::Blue;
  }
}
