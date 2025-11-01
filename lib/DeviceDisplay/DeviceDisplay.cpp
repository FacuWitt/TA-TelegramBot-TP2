#include "DeviceDisplay.h"

DeviceDisplay::DeviceDisplay(TwoWire *wire)
    : _display(128, 64, wire, -1) {
  _display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  _display.clearDisplay();
  _display.setTextSize(1);
  _display.setTextColor(SSD1306_WHITE);
  _display.setCursor(0, 0);
  _display.display();
      // Wire.begin();
}

void DeviceDisplay::showLedStatus(const String &ledName, bool isOn) {
  _display.clearDisplay();
  _display.setCursor(0, 0);
  _display.print(ledName);
  _display.print(": ");
  _display.println(isOn ? "Encendido" : "Apagado");
  _display.display();
}

void DeviceDisplay::showDHT22Readings(float temperature, float humidity) {
  _display.clearDisplay();
  _display.setCursor(0, 0);
  _display.println("DHT22 Readings:");
  _display.print("Temp: ");
  _display.print(temperature);
  _display.println(" C");
  _display.print("Humedad: ");
  _display.print(humidity);
  _display.println(" %");
  _display.display();
}

void DeviceDisplay::showPoteValue(int poteValue) {
  _display.clearDisplay();
  _display.setCursor(0, 0);
  _display.println("Valor Pote:");
  _display.println(poteValue);
  _display.display();
}
