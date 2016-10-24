#include <ESP8266HTTPClient.h>
#include <FastLED.h>

#define WIFI_SSID "iot-workshop"
#define WIFI_PASSWORD  "PoweredByTopicus"

#define MQTT_SERVER_HOST ""
#define MQTT_SERVER_PORT 1883

#define JENKINS_URL "http://192.168.40.2:8080/job/"


String MQTT_TOPICS[2] = {"jenkins/job/test/","jenkins/job/test2/"};
String JENKINS_JOBS[2] = {"test/build?delay=0sec","test2/build?delay=0sec"};


bool updateBuildStatus[2] = {false,false};
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
  bool changed=false;
  for(int x=0; x<4; x++) {
    for(int i=0; i<2; i++) {
      if(updateBuildStatus[i]) {
        dimRgbLed(i,192);
        changed=true;
      }
    }
    if(changed) {
      FastLED.show();
      delay(100);
    }
    for(int i=0; i<2; i++) {
      if(updateBuildStatus[i]) {
        setRgbLed(i, lastColor[i]);
      }
    }
    if(changed) {
      FastLED.show();
      delay(100);
    }
  }
}

void doBuild0() {
  doBuild(0);
}

void doBuild1() {
  doBuild(1);
}

void doBuild(int nr) {
  updateBuildStatus[nr] = true;
  Serial.print("doBuild");
  Serial.println(nr);
  HTTPClient http;
  http.begin(JENKINS_URL+JENKINS_JOBS[nr]);
  int httpCode = http.GET();
  if(httpCode == 201) {
    Serial.println("OK: HTTP 201 Created");
  }
  else
  {
    updateBuildStatus[nr] = false;
    Serial.print("NOT OK: HTTP ");
    Serial.println(httpCode);
  }
}
