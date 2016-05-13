#include <ESP8266HTTPClient.h>

boolean reported = false;

void report() {
  Serial.println("Reporting");
  updateTemperature();
  updateLight();

  const char* light_state = ((lastLux > 0) ? "1" : "0");
  const char* temp_state = ((lastTemperature > 0) ? "1" : "0");

  char temp_value[10];
  dtostrf(lastTemperature, 1, 2, temp_value);

  char light_value[10];
  dtostrf(lastLux, 1, 2, light_value);

  docs(light_state, temp_state, temp_value, light_value);
}

void docs(const char* light_state, const char* temp_state, char* temp_value, char* light_value) {
  String data;
  data += "https://docs.google.com/forms/d/1aKtosgA0Q0woMy_FbvWl3Q-Z8jQyjt4yXkNLpvyPMFY/formResponse?";
  data += "entry.1718414522=";
  data += mac;
  data += "&entry.1272450683=";
  data += light_state;
  data += "&entry.776780075=";
  data += temp_state;
  data += "&entry.434994815=";
  data += temp_value;
  data += "&entry.695034911=";
  data += light_value;

  Serial.println(data);

  HTTPClient http;
  http.begin(data); 
  
  int httpCode = http.GET();
  if(httpCode == 200) {
    Serial.println("OK");
  } else {
    Serial.print(httpCode);
    Serial.println("FAIL");
  }

  http.end();
}

void loopReport() {
  if (!reported && millis() > 10000) {
      report();
      reported = true;
  }
}

