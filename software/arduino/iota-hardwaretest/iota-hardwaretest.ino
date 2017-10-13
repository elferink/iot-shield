#include <ESP8266WiFi.h>
#include "OneButton.h"
#include <Wire.h>
#include <LM75.h>
#include <FastLED.h>
#include <PubSubClient.h>

/**
   Config, pas onderstaande waardes aan!
*/
#define WIFI_SSID           "LessWire"
#define WIFI_PASSWORD       "yo-mama123"
#define RGB_LED_BRIGHTNESS  10 // 0-255

#define MQTT_SERVER         "52.57.219.134"
#define MQTT_PORT           1883
#define MQTT_USERNAME       ""
#define MQTT_PASSWORD       ""
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
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

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
  singleClick();
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
   MQTT callback, wordt aangroepen bij ontvangst van een bericht
 */
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  char content[length + 1];
  memcpy(content, payload, length);
  content[length] = 0;

  String topic_str = String(topic);
  Serial.print("Ontvangen op ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(content);
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

  // Wifi instellen
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Wifi verbinden");

  // Wachten tot wifi verbonden is
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println(" verbonden!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  // MQTT configureren
  mqtt_client.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt_client.setCallback(mqtt_callback);
  
  // Lees beide sensoren uit
  readSensors();
}

/*
   Functie wordt continue aangroepen, voeg hier je eigen logica aan toe
*/
void loop() {
  // Laat knop controleren of er activiteit geweest is
  button.tick();
  if(getLuminance() > 40 ) {
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
  }
}
