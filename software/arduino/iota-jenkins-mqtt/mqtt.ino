#include <PubSubClient.h>

PubSubClient client(espClient);
char base_topic[100];
char will_topic[200];
char* mqtt_node_id;

void mqtt_reconnect() {
  while (!client.connected()) {
    Serial.println("mqtt reconnect");

    if (client.connect(mqtt_node_id)) {
      Serial.println("mqtt connected");
      client.subscribe(jenkins_status_topic_1);
      client.subscribe(jenkins_status_topic_2);
    } else {
      Serial.print("mqtt connected failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  char content[length + 1];
  memcpy(content, payload, length);
  content[length] = 0;

  String topic_str = String(topic);
  uint8_t current_status = getBuildStatus(content);

  if (topic_str.endsWith(jenkins_status_topic_1)) {
    statusColor(0, current_status);
  } else if (topic_str.endsWith(jenkins_status_topic_2)) {
    statusColor(1, current_status);
  }
}

void setupMqtt() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  String client_id = "jenkins-";
  client_id += String(random(0xffffff), HEX);
  mqtt_node_id = (char*)client_id.c_str();
}

void loopMqtt() {
  if (!client.connected()) {
    mqtt_reconnect();
  } else {
    client.loop();
  }
}

