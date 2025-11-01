#include "DevicePote.h"

DevicePote::DevicePote(int pin) : _pin(pin) {
  pinMode(_pin, INPUT);
}
int DevicePote::read() {
  return analogRead(_pin);
}
