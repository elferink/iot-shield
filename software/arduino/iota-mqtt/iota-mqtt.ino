const char* ssid = "";        
const char* password = "";  

const char* mqtt_node_id = "iota-mqtt";
const char* mqtt_server = "";

void setupGeneral() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
}

void setup() {
  setupGeneral();
  setupWifi();
  setupMqtt();
  setupTemperature();
  setupLight();
  setupLed();
  setupButton();
  setupApa();
}

void loop() {
  loopMqtt();
  loopTemperature();
  loopLight();
  loopButton();
}
