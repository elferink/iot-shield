#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "OneButton.h"

#define WIFI_SSID           "My Wifi"
#define WIFI_PASSWORD       "My Password"

#define IFTTT_URL           "http://maker.ifttt.com"
#define IFTTT_KEY           "IFTTT KEY";
#define IFTTT_EVENT         "IFTTT EVENT NAME";

#define BUTTON_PIN          0   // D3
OneButton button(BUTTON_PIN, true);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Wifi verbinden");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" verbonden!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  pinMode(BUTTON_PIN, INPUT);
  button.attachClick(singleClick);
}

void loop() {
  button.tick();
}

void singleClick() {
  String url;
  url += IFTTT_URL;
  url += "/trigger/";
  url += IFTTT_EVENT;
  url += "/with/key/";
  url += IFTTT_KEY;

  HTTPClient http;
  http.begin(url); 
  
  int httpCode = http.GET();
  if(httpCode == 200) {
    Serial.println("IFTTT OK");
  } else {
    Serial.print(httpCode);
    Serial.println("IFTTT FAIL");
  }

  http.end();
}

