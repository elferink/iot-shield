#include <PubSubClient.h>

PubSubClient client(espClient);
char base_topic[100];
char will_topic[200];

void mqtt_reconnect() {
  while (!client.connected()) {
    Serial.println("mqtt reconnect");

    if (client.connect(mqtt_node_id, will_topic, 2, true, "OFF")) {
      Serial.println("mqtt connected");
      client.publish(will_topic, "ON");

      char topic_led[200];
      sprintf(topic_led, "%s/%s", base_topic, "led");
      client.subscribe(topic_led);

      char topic_rgb[200];
      sprintf(topic_rgb, "%s/%s", base_topic, "rgb/#");
      client.subscribe(topic_rgb);
    } else {
      delay(1000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  char content[length + 1];
  memcpy(content, payload, length);
  content[length] = 0;

  String topic_str = String(topic);
  Serial.print("Received on ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(content);

  if (topic_str.endsWith("led")) {
    if (strcmp(content, "ON") == 0) {
      ledOn();
    } else {
      ledOff();
    }
  }
  else if (topic_str.indexOf("rgb") != -1) {
    int r, g, b;

    r = getValue(content, ' ', 0).toInt();
    g = getValue(content, ' ', 1).toInt();
    b = getValue(content, ' ', 2).toInt();

    if (topic_str.endsWith("0")) {
      setLed(0, r, g, b);
    }
    else if (topic_str.endsWith("1")) {
      setLed(1, r, g, b);
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
  client.publish(full_topic, value);
}

void setupMqtt() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  sprintf(base_topic, "actuator/%s", mac);
  sprintf(will_topic, "%s/%s", base_topic, "state");
}

void loopMqtt() {
  if (!client.connected()) {
    mqtt_reconnect();
  } else {
    client.loop();
  }
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

