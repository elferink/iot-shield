const char* ssid = "";        
const char* password = "";  

void setupGeneral() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
}

void setup() {
  setupGeneral();
  setupWifi();
  setupTemperature();
  setupLed();
  setupButton();
  setupApa();
}

void loop() {
  loopButton();
  loopApa();
  loopReport();
  loopWifi();
}
