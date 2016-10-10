const char* ssid = "";        
const char* password = "";

const char* mqtt_server = "";
const char* mqtt_username = "";
const char* mqtt_password = "";
const int   mqtt_port = 1883;

void setupGeneral() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
}

void setup() {
  setupGeneral();
  setupWifi();
  setupMqtt();
  setupLed();
  setupButton();
  setupApa();
}

void loop() {
  loopButton();
  loopMqtt();
  loopApa();
}
