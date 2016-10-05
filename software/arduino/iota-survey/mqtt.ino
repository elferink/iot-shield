#include <PubSubClient.h>

PubSubClient client(espClient);
char base_topic[200];
char node_topic[200];
char will_topic[300];
char vote_topic[300];
char vote_value[10];
char* mqtt_node_id;

void mqtt_reconnect() {
  while (!client.connected()) {
    Serial.println("mqtt reconnect");

    if (client.connect(mqtt_node_id, mqtt_username, mqtt_password, will_topic, 2, false, "0")) {
      Serial.println("mqtt connected");
      client.publish(will_topic, "1");

      char topic_survey_settings[300];
      sprintf(topic_survey_settings, "%s/%s", base_topic, "actions/#");
      client.subscribe(topic_survey_settings);

      char topic_node_config[300];
      sprintf(topic_node_config, "%s/%s", node_topic, "config/#");
      client.subscribe(topic_node_config);
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

  if (topic_str.endsWith("config/color")) {
    String hexstring = String(content);

    // Get rid of '#' and convert it to integer
    long number = strtol( &hexstring[1], NULL, 16);

    // Split them up into r, g, b values
    long r = number >> 16;
    long g = number >> 8 & 0xFF;
    long b = number & 0xFF;

    clr.r = r;
    clr.g = g;
    clr.b = b;

    if (enabled) {
      setRgbLeds(clr);
    }
  }
  else if (topic_str.endsWith("config/value")) {
    memset(vote_value, 0, 10);
    memcpy(vote_value, payload, length);
    vote_value[length] = 0;
  } else if (topic_str.endsWith("actions/vote")) {
    if (enabled) {
      String node_id = getValue(content, ' ', 0);
      if (node_id == survey_node_id) {
        setBlink();
      } else {
        setFade();
      }
    }
  } else if (topic_str.endsWith("actions/enabled")) {
    if (strcmp(content,"1") != 0) {
      disableSurvey();
    } else {
      enableSurvey();
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
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  String client_id = "vote-";
  client_id += survey_node_id;
  client_id += String(random(0xffff), HEX);
  mqtt_node_id = (char*)client_id.c_str();

  sprintf(base_topic, "survey/%s", survey_id);                    // survey/c933f812-2c71-4bd1-8780-b22e00de42eb/
  sprintf(vote_topic, "%s/actions/vote", base_topic);             // survey/c933f812-2c71-4bd1-8780-b22e00de42eb/actions/vote
  sprintf(node_topic, "%s/nodes/%s", base_topic, survey_node_id); // survey/c933f812-2c71-4bd1-8780-b22e00de42eb/nodes/1
  sprintf(will_topic, "%s/runtime/state", node_topic);            // survey/c933f812-2c71-4bd1-8780-b22e00de42eb/nodes/1/runtime/state

  Serial.print("base_topic: ");
  Serial.println(base_topic);
  Serial.print("node_topic: ");
  Serial.println(node_topic);
  Serial.print("will_topic: ");
  Serial.println(will_topic);
  Serial.print("vote_topic: ");
  Serial.println(vote_topic);
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

