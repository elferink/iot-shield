const char* ssid = "";        
const char* password = "";

const char* survey_id = "";         // Example: c933f812-2c71-4bd1-8780-b22e00de42eb
const char* survey_node_id = "";    // Example: 1, 2 or 3

const char* mqtt_server = "";
const char* mqtt_username = "";
const char* mqtt_password = "";
const int   mqtt_port = 0;

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
