#include "ThingSpeakClient.h"

ThingSpeakClient ::ThingSpeakClient(const char* server, const String apiKey)
    :  _server(server), _apiKey(apiKey) {}

void ThingSpeakClient::sendData(float temperature, float humidity) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

            // Construir la URL de envío
            String url = _server + String("?api_key=") + _apiKey +
                    "&field1=" + String(temperature) +
                    "&field2=" + String(humidity);

        http.begin(url);
        int httpCode = http.GET();

        if (httpCode > 0) {
        Serial.printf("ThingSpeak: %d\n", httpCode);
        } else {
        Serial.println("Error en HTTP");
        }
        http.end();
    } else {
        Serial.println("WiFi no conectado");
    }
}