#include "DeviceLed.h"

DeviceLed::DeviceLed(int pin) : _pin(pin) {
  pinMode(_pin, OUTPUT);
}
void DeviceLed::on() {
  digitalWrite(_pin, HIGH);
}
void DeviceLed::off() {
  digitalWrite(_pin, LOW);
}