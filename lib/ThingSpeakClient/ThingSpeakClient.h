#ifndef THINGSPEAKCLIENT_H
#define THINGSPEAKCLIENT_H
#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>

class ThingSpeakClient {
  public:
    ThingSpeakClient(const char* server, const String apiKey);
    void sendData(float field1, float field2);
  private:
    const char* _server;
    String _apiKey;
};

#endif