#include "DeviceDHT22.h"


DeviceDHT22::DeviceDHT22(int pin) : _dht(pin, DHT22) {
    pinMode(pin, INPUT); // Pin del sensor DHT22
    _dht.begin();
}

float DeviceDHT22::readTemperature() {
  sensors_event_t event;
  _dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error leyendo la temperatura!"));
    return -1;
  }
  else {
    return event.temperature;
  }
}

float DeviceDHT22::readHumidity() {
  sensors_event_t event;
  _dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error leyendo la humedad!"));
    return -1;
  }
  else {
    return event.relative_humidity;
  }
}