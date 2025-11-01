#ifndef _DEVICELED_H
#define _DEVICELED_H
#include <Arduino.h>

class DeviceLed {
  public:
    DeviceLed(int pin);
    void on();
    void off();
    bool isOn() {
      return digitalRead(_pin) == HIGH;
    }
  private:
    int _pin;
};

#endif