#include <Wire.h>
#include <LM75.h>

LM75 sensor;

int temperature_lastUpdate = 0;
int temperature_update_interval = 10000; // 10 seconds

float lastTemperature = 0;

void setupTemperature() {
  Wire.begin();
  updateTemperature();
}

void updateTemperature() {
  sensor.shutdown(false);
  lastTemperature = sensor.temp();;
  
  Serial.print(lastTemperature);
  Serial.println(" C");
  
  sensor.shutdown(true);
}

void loopTemperature() {
  if (millis() > temperature_update_interval && 
      (millis() - temperature_update_interval) > temperature_lastUpdate) {
    updateTemperature();
    temperature_lastUpdate = millis();
  }
}

