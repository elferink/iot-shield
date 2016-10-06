#define WIFI_SSID ""
#define WIFI_PASSWORD  ""

#define MQTT_SERVER_HOST "firefly.topicus.local"
#define MQTT_SERVER_PORT 1883

#define MQTT_TOPIC_1 "jenkins/job/iot-workshop/"
#define MQTT_TOPIC_2 "jenkins/job/Cobra_master/"

#include <ESP8266HTTPClient.h>
#include <FastLED.h>

bool updateBuildStatus = false;
CRGB lastColor[2];
void setRgbLed(short ledno, CRGB color);

void setupGeneral() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
}

void setup() {
  setupGeneral();
  setupWifi();
  setupButton();
  setupApa();
  setupMqtt();
}

void loop() {
  loopButton();
  loopMqtt();
  if(updateBuildStatus) {
    dimRgbLed(0,192);
    FastLED.show();
    delay(100);
    setRgbLed(0, lastColor[0]);
    FastLED.show();
    delay(100);
  }
}

void doBuild() {
  updateBuildStatus = true;
  Serial.println("doBuild");
  HTTPClient http;
  http.begin("http://192.168.56.103:8080/buildByToken/build?job=iot-workshop&token=SuperSecret");
  int httpCode = http.GET();
  if(httpCode == 201) {
    Serial.println("OK: HTTP 201 Created");
  }
  else
  {
    updateBuildStatus = false;
    Serial.print("NOT OK: HTTP ");
    Serial.println(httpCode);
  }
}
