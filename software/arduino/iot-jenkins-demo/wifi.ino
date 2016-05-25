#include <ESP8266WiFi.h>

WiFiClient espClient;
char mac[18];

boolean wifi_connected = false;

void setupWifi() {
  WiFi.mode(WIFI_STA);

  uint8_t MAC_array[6];
  WiFi.macAddress(MAC_array);
  for (int i = 0; i < sizeof(MAC_array); ++i) {
    char *pattern = "%s%02x-";
    if (i == sizeof(MAC_array) - 1) {
      pattern = "%s%02x";
    }
    sprintf(mac, pattern, mac, MAC_array[i]);
  }

  Serial.print("Mac: ");
  Serial.println((char*)mac);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Wifi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loopWifi() {
  if (!wifi_connected) {
    if (WiFi.status() == WL_CONNECTED) {
      wifi_connected = true;
      Serial.println("Wifi connected");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
    }
  }
}

