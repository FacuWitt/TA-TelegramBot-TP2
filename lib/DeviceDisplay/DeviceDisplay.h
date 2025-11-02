
#ifndef _DEVICEDISPLAY_H
#define _DEVICEDISPLAY_H
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class DeviceDisplay {
public:
  DeviceDisplay(TwoWire *wire = &Wire);

  void begin();
  void showLedStatus(const String &ledName, bool isOn);
  void showDHT22Readings(float temperature, float humidity);
  void showPoteValue(int poteValue);


//   void begin();
//   void clear();
//   void display();
//   void print(const String &text);
//   void setCursor(int x, int y);
//   void setTextSize(int size);
//   void setTextColor(uint16_t color);

private:
  Adafruit_SSD1306 _display;
};

#endif
