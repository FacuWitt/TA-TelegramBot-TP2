#ifndef DEVICEDHT22
#define DEVICEDHT22
#include <DHT_U.h>

class DeviceDHT22 {
  public:
    DeviceDHT22(int pin);
    float readTemperature();
    float readHumidity();
  private:
    DHT_Unified _dht;
};
#endif