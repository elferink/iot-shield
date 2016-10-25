#include <AsyncMqttClient.h>

AsyncMqttClient mqttClient;

char base_topic[200];
char will_topic[300];
char game_topic[300];
char* mqtt_node_id;

int game_number = 0;
int game_status = 0;
int old_status = -1;

int go_time = 0;
int response_time = 0;

#define STATUS_WAITING    0
#define STATUS_READY      1
#define STATUS_GO         2
#define STATUS_FINISHED   3

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

void onMqttConnect(bool sessionPresent) {
  Serial.println("mqtt connected");
  mqttClient.publish(will_topic, 2, true, "1");
  mqttClient.subscribe(game_topic, 2);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  char content[len + 1];
  memcpy(content, payload, len);
  content[len] = 0;

  String topic_str = String(topic);
  Serial.print("Received on ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(content);

  if (topic_str.endsWith("/number")) {
    int new_game_number = atoi(content);

    Serial.print("Game number: ");
    Serial.println(new_game_number);

    char unsub_topic[300];
    sprintf(unsub_topic, "%s/%d/#", base_topic, game_number);                        // game/10/#
    mqttClient.unsubscribe(unsub_topic);
    Serial.print("Unsubscribed: ");
    Serial.println(unsub_topic);

    game_number = new_game_number;

    char sub_topic[300];
    sprintf(sub_topic, "%s/%d/#", base_topic, game_number);                        // game/10/#
    mqttClient.subscribe(sub_topic, 2);

    Serial.print("Subscribed: ");
    Serial.println(sub_topic);

    pressed = false;
    old_status = game_status;
    game_status = STATUS_WAITING;
    updateGameStatus();
  } else {
    String game_no = getValue(topic_str, '/', 1);
    int game_no_received = game_no.toInt();
    if (game_no_received == game_number) {
      if (topic_str.endsWith("/status")) {
        old_status = game_status;
        if (strcmp(content, "WAITING") == 0) {
          game_status = STATUS_WAITING;
        } else if (strcmp(content, "READY") == 0) {
          game_status = STATUS_READY;
        } else if (strcmp(content, "GO") == 0) {
          game_status = STATUS_GO;
        } else if (strcmp(content, "FINISHED") == 0) {
          game_status = STATUS_FINISHED;
        }
        Serial.print("Game status: ");
        Serial.println(game_status);
        updateGameStatus();
      } else if (topic_str.endsWith("/winner")) {
        Serial.print("Game winner: ");
        Serial.println(content);
        if (strcmp(content, mac) == 0) {
          Serial.print("We won!");
          setRgbLed(1, CRGB::Green);
        } else {
          Serial.print("We lost..");
          setRgbLed(1, CRGB::Red);
        }
      }
    } else {
      Serial.println("Invalid game number");
    }
  }
}

void pubInt(char *topic, int value) {
  char b[10];
  sprintf(b, "%d", value);
  pub(topic, b);
}

void pubFloat(char *topic, float value) {
  char b[10];
  dtostrf(value, 1, 2, b);
  pub(topic, b);
}

void pub(char *topic, char *value) {
  char full_topic[200];
  sprintf(full_topic, "%s/%s", base_topic, topic);
  mqttClient.publish(full_topic, 2, false, value);
}

void setupMqtt() {
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onMessage(onMqttMessage);

  String client_id = "game-";
  client_id += mac;
  client_id += String(random(0xff), HEX);
  mqtt_node_id = (char*)client_id.c_str();

  sprintf(base_topic, "game");                                    // game
  sprintf(game_topic, "%s/number", base_topic);                   // game/number
  sprintf(will_topic, "%s/clients/%s", base_topic, mac);          // game/clients/00-aa-bb-cc-11

  Serial.print("base_topic: ");
  Serial.println(base_topic);
  Serial.print("game_topic: ");
  Serial.println(game_topic);
  Serial.print("will_topic: ");
  Serial.println(will_topic);

  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setKeepAlive(5).setCleanSession(false).setWill(will_topic, 2, true, "0").setClientId(mqtt_node_id);
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();

}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void updateGameStatus() {
  if (old_status != game_status) {
    switch (game_status) {
      case STATUS_WAITING:
        setRgbLed(1, CRGB::Black);
        setRgbLed(0, CRGB::Red);
        break;
      case STATUS_READY:
        setRgbLed(1, CRGB::Black);
        setRgbLed(0, CRGB::Yellow);
        break;
      case STATUS_GO:
        setRgbLed(1, CRGB::Black);
        go_time = millis();
        pressed = false;
        setRgbLed(0, CRGB::Green);
        break;
      case STATUS_FINISHED:
        pressed = false;
        setRgbLed(0, CRGB::Blue);
        break;
    }
  }
}


