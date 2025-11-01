#ifndef _DEVICEPOTE_H
#define _DEVICEPOTE_H
#include <Arduino.h>

class DevicePote {
  public:
    DevicePote(int pin);
    int read();
  private:
    int _pin;
};

#endif