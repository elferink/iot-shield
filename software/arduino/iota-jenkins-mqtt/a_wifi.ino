WiFiClient espClient;
char mac[18];

void setupWifi() {
  WiFi.mode(WIFI_STA);
 
  Serial.println("Connecting wifi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

