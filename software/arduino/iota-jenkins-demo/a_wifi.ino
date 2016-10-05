#include <ESP8266WiFi.h>

WiFiClient espClient;
char mac_address[18];

void setupWifi() {
  WiFi.mode(WIFI_STA);

  uint8_t MAC_array[6];
  char buf[18];
  WiFi.macAddress(MAC_array);
  for (int i = 0; i < sizeof(MAC_array); ++i) {
    char *pattern = "%s%02x";
    sprintf(mac_address, pattern, mac_address, MAC_array[i]);
  }

  Serial.print("Mac: ");
  Serial.println((char*)mac_address);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Wifi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}
