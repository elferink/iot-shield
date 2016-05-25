const char* ssid = "iot-workshop";        
const char* password = "123456ab"; 

const uint8_t BUILD_SUCCESS = 0;
const uint8_t BUILD_FAIL = 1;
const uint8_t BUILD_UNSTABLE = 2;
const uint8_t BUILD_WAIT = 3;

uint8_t lastChecked = 0;
uint8_t status;

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

void setupGeneral() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  status = BUILD_WAIT;
}

void setup() {
  setupGeneral();
  setupWifi();
  setupButton();
  setupApa();
}

void loop() {
  loopButton();
  if (millis() - lastChecked > 5000) {   
    getBuildStatus();
    lastChecked = millis();
    statusColor(status);
  }
}

void doBuild() {
  Serial.println("doBuild");
  HTTPClient http;
  http.begin("http://172.16.33.228:8080/job/test/build?delay=0sec");
  int httpCode = http.GET();
  if(httpCode == 200) {
    status = BUILD_WAIT;
    statusColor(status);
    Serial.println("HTTP OK");
  }
  else
  {
    Serial.println("HTTP NOT OK");
  }
}

void getBuildStatus() {
  Serial.println("getBuildStatus");
  HTTPClient http;
  http.begin("http://172.16.33.228:8080/job/test/lastBuild/api/json?tree=number,result");
  int httpCode = http.GET();
  if(httpCode == 200) {
    StaticJsonBuffer<200> jsonBuffer;
    String response = http.getString();
    JsonObject& json = jsonBuffer.parseObject(response);
    Serial.println("json: " + response);
    status = stringToStatus(json["result"]);
  }
}

uint8_t stringToStatus(const char* str) {
  Serial.print("stringToStatus: ");
  Serial.println(str);
  if(strcmp("SUCCESS",str)==0) {
    return BUILD_SUCCESS;
  }
  if(strcmp("UNSTABLE",str)==0) {
    return BUILD_UNSTABLE;
  }
  return BUILD_FAIL;
}

