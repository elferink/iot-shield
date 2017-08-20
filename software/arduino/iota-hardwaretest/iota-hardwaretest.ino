#include <ESP8266WiFi.h>
#include "OneButton.h"
#include <Wire.h>
#include <LM75.h>
#include <FastLED.h>

/**
   Config, pas onderstaande waardes aan!
*/
#define WIFI_SSID           "iot-workshop"
#define WIFI_PASSWORD       "PoweredByTopicus"
#define RGB_LED_BRIGHTNESS  10 // 0-255

/*
   Constanten
*/
#define BUTTON_PIN          0   // D3
#define LED_PIN             2   // D4

#define RGB_LED_DATA_PIN    13  // D7
#define RGB_LED_CLOCK_PIN   14  // D5
#define RGB_NUM_LEDS        2
#define RGB_LED_TYPE        APA102
#define RGB_COLOR_ORDER     BGR

/*
     Runtime variabelen
*/
OneButton button(BUTTON_PIN, true);
LM75 temp_sensor;
CRGB leds[RGB_NUM_LEDS];

boolean led_on = false;
boolean rgb_leds_on = false;
boolean cycle = false;
short cycle_idx = 0;
CRGB cycle_arr[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Black};

/*
   Functies om gebruik van de knop af te handelen
*/
void singleClick() {
  cycle = !cycle;
}

void doubleClick() {
  rgb_leds_on = !rgb_leds_on;

  if (rgb_leds_on) {
    setRgbLeds(CRGB::Green);
  } else {
    setRgbLeds(CRGB::Black);
  }
}

void longPress() {
  readSensors();
}

/*
   Temperatuursensor
*/
float getTemperature() {
  // Sensor activeren
  temp_sensor.shutdown(false);
  delay(100);

  float temperature = temp_sensor.temp();

  // Sensor deactiveren
  temp_sensor.shutdown(true);

  return temperature;
}

/*
   Lichtsensor
*/
float getLuminance() {
  // Meet voltage op analoge input en reken dit om in het equivalente aantal lux
  float volts = analogRead(A0) * 3.3 / 1024.0;
  float amps = volts / 10000.0;  // 10k weerstand
  float microamps = amps * 1000000;
  float lux = microamps * 2.0;

  return lux;
}

/*
   Lees sensoren uit
*/
void readSensors() {
  Serial.print("Temperatuur: ");
  Serial.print(getTemperature());
  Serial.println("°C");

  Serial.print("Hoeveelheid licht: ");
  Serial.print(getLuminance());
  Serial.println(" lux");
}

/*
   Reguliere led
*/
void setLed(bool state) {
  digitalWrite(LED_PIN, !state);
}

/*
   RGB leds
*/
void setRgbLeds(CRGB color) {
  for (int i = 0; i < RGB_NUM_LEDS; i++) {
    setRgbLed(i, color);
  }
}

void setRgbLed(int ledno, CRGB color) {
  leds[ledno] = color;
  FastLED.show();
}

/*
   Deze functie wordt eenmalig aangroepen bij opstarten
*/
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();

  // Knop instellen
  pinMode(BUTTON_PIN, INPUT);
  button.setClickTicks(300);
  button.setPressTicks(600);
  button.attachClick(singleClick);
  button.attachDoubleClick(doubleClick);
  button.attachLongPressStart(longPress);

  // Start I2C voor temperatuursensor
  Wire.begin();

  // Reguliere led instellen
  pinMode(LED_PIN, OUTPUT);
  setLed(false); // led uit

  // Initialiseer RGB leds
  FastLED.addLeds<RGB_LED_TYPE, RGB_LED_DATA_PIN, RGB_LED_CLOCK_PIN, RGB_COLOR_ORDER>(leds, RGB_NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(RGB_LED_BRIGHTNESS);
  setRgbLeds(CRGB::Black); // beide leds uit

  // Lees beide sensoren uit
  readSensors();
}

/*
   Functie wordt continue aangroepen, voeg hier je eigen logica aan toe
*/
void loop() {
  // Laat knop controleren of er activiteit geweest is
  button.tick();
  if(getLuminance() > 200 ) {
    led_on = true;
  }
  else
  {
    led_on = false;
  }
  setLed(led_on);

  EVERY_N_SECONDS(1) {
    if(cycle) {
      setRgbLeds(cycle_arr[cycle_idx]);
      cycle_idx++;
      if(cycle_idx>3) {
        cycle_idx=0;
      }
    }
    else
    {
      if(getTemperature() > 20.0) {
        setRgbLeds(CRGB::Pink);
      }
    }
  }
}
