#include <Wire.h>
#include <LM75.h>

LM75 sensor;

int temperature_lastUpdate = 0;
int temperature_update_interval = 10000; // 10 seconds

float lastTemperature = 0;

void setupTemperature() {
  Wire.begin();
}

void updateTemperature() {
  sensor.shutdown(false);
  delay(100);
  lastTemperature = sensor.temp();;
  
  Serial.print(lastTemperature);
  Serial.println(" C");
  
  sensor.shutdown(true);
}

