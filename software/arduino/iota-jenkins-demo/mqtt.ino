#include <PubSubClient.h>

PubSubClient client(espClient);
char base_topic[100];
char will_topic[200];
String mqtt_node_id = "iota-mqtt-";

void mqtt_reconnect() {
  while (!client.connected()) {
    Serial.println("mqtt connect, node ID: ");
      Serial.println(mqtt_node_id);

    if (client.connect((char*)mqtt_node_id.c_str())) {
      Serial.println("mqtt connected");
      client.subscribe(MQTT_TOPIC_1);
      client.subscribe(MQTT_TOPIC_2);
    } else {
      Serial.print("mqtt connected failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, short length) {
  char content[length + 1];
  memcpy(content, payload, length);
  content[length] = 0;

  String topic_str = String(topic);
  short current_status = stringToStatus(content);

  Serial.print("Status changed for topic: ");
  Serial.print(topic);
  Serial.print(" to ");
  Serial.println(content);

  if (topic_str.endsWith(MQTT_TOPIC_1)) {
    statusColor(0, current_status);
  } else if (topic_str.endsWith(MQTT_TOPIC_2)) {
    statusColor(1, current_status);
  }
}

void setupMqtt() {
  client.setServer(MQTT_SERVER_HOST, MQTT_SERVER_PORT);
  client.setCallback(callback);

  mqtt_node_id.concat(mac_address);
}

void loopMqtt() {
  if (!client.connected()) {
    mqtt_reconnect();
  } else {
    client.loop();
  }
}

