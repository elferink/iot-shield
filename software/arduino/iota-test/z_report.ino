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
  data += "http://api.thingspeak.com/update?api_key=0D8KKHE9VNC7YCEZ"
  data += "&field1=";
  data += mac;
  data += "&field2=";
  data += light_state;
  data += "&field3=";
  data += temp_state;
  data += "&field4=";
  data += temp_value;
  data += "&field5=";
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

