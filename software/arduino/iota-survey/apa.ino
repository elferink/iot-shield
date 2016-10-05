#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    2
#define BRIGHTNESS  29
#define LED_TYPE    APA102
#define COLOR_ORDER BGR

CRGB leds[NUM_LEDS];

#define APADATAPIN 13 // D7
#define APACLOCKPIN 14 // D5

void setRgbLeds(CRGB color);
void setRgbLed(int ledno, CRGB color);

boolean fade_apa = false;
boolean blink_apa = false;
int level = BRIGHTNESS;
int level_change = 1;
int blink_no = 1;

unsigned long back_on_time = 0;

boolean enabled = true;
CRGB clr = CRGB::Black;


void setupApa() {
  FastLED.addLeds<LED_TYPE, APADATAPIN, APACLOCKPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  setRgbLeds(clr);
}

void loopApa() {
  if (fade_apa) {
    EVERY_N_MILLISECONDS(5) {
      if (level <= 8) {
        setRgbLeds(CRGB::Black);
        fade_apa = false;
        back_on_time = millis() + 1000;
      } else {
        FastLED.setBrightness(dim8_video(level));
        FastLED.show();
        level = level - level_change;
      }
    }
  } else if (blink_apa) {
    EVERY_N_MILLISECONDS(17) {
      if (blink_no > 4) {
        blink_apa = false;
      } else {
        if (level <= 18 || level > 82) {
          level_change = -level_change;
          blink_no++;
        }
        FastLED.setBrightness(dim8_video(level));
        FastLED.show();
        level = level - level_change;
      }
    }
  }

  if (back_on_time > 0 && millis() > back_on_time) {
      FastLED.setBrightness(BRIGHTNESS);
      setRgbLeds(clr);
      back_on_time = 0; 
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

void setFade() {
  fade_apa = true;
  level = 82;
  level_change = 1;
}

void setBlink() {
  blink_apa = true;
  level = 82;
  level_change = 4;
  blink_no = 1;
}

void enableSurvey() {
  enabled = true;
  setRgbLeds(clr);
}

void disableSurvey() {
  enabled = false;
  setRgbLeds(CRGB::Black);
}
