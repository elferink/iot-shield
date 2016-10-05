#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";

const char* mqtt_server = "";

const char* jenkins_status_topic_1 = "";
const char* jenkins_status_topic_2 = "";

void setupGeneral() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
}

void setup() {
  setupGeneral();
  setupWifi();
  setupMqtt();
  setupApa();
}

void loop() {
  loopMqtt();
}
