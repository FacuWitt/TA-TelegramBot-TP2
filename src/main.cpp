#include <Arduino.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <HTTPClient.h>
#include "ThingSpeakClient.h"
#include "DevicePote.h"
#include "DeviceDHT22.h"
#include "DeviceLED.h"
#include "DeviceDisplay.h"


const char *SSID = "iPhone de Valentina";
const char *PASS = "valentina.";


const char * BOT_TOKEN = "7124446827:AAFv--a_PUer1BIEvi0C3gihOJ1_zACVnqk";
const unsigned long SCAN_TIME = 1000;

const int pinLED_2 = 2;
const int pinLED_23 = 23;
const int pinPote = 32; // Pin del potenciómetro
const int pinDHT22 = 33; // Pin del sensor DHT22


String apiKey = "L8TEPTW9E18XF6QL";
const char* server = "http://api.thingspeak.com/update";

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// Inicializar objetos de los dispositivos y servicios

ThingSpeakClient thingSpeakClient(server, apiKey);
DeviceDisplay display(&Wire);
DeviceDHT22 dht22(pinDHT22);
DeviceLed led2(pinLED_2);
DeviceLed led23(pinLED_23);
DevicePote pote(pinPote);


WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client); // HTTPS
unsigned long previus;


void handleMessages(int n){
  // Barre menasajes nuevos, cada cierto tiempo n
  Serial.printf("Se recibieron %d mensajes nuevos\n", n);
  for(size_t i = 0; i < n; i++){
    String chat_id = bot.messages[i].chat_id; // informativo
    String text = bot.messages[i].text;  // contenido de cada mensaje

    // MENSAJE DE BIENVENIDA + mostrar opciones del menu
    if(text == "/start"){
      String welcome = "¡Bienvenido! Soy tu bot de ESP32.\n";
      welcome += "Comandos disponibles:\n";
      welcome += "/led23On : Enciende el LED VERDE\n";
      welcome += "/led23Off : Apaga el LED VERDE\n";
      welcome += "/led2On : Enciende el LED AZUL\n";
      welcome += "/led2Off : Apaga el LED AZUL\n";
      welcome += "/dht22 : Muestra temperatura y humedad\n";
      welcome += "/pote : Muestra valor del potenciómetro\n";
      welcome += "/platiot : Enviar los valores de humedad y temperatura a arduino Cloud\n";
      welcome += "/displayLed23 : Muestra el estado del LED Verde en el display de la placa\n";
      welcome += "/displayLed2 : Muestra el estado del LED Azul en el display de la placa\n";
      welcome += "/displayPote : Muestra el valor del potenciómetro en el display de la placa\n";
      welcome += "/displayDHT22 : Muestra los valores de temperatura y humedad en el display de la placa\n";


      bot.sendMessage(chat_id, welcome, "");
    }
    else if(text == "/led23On"){ 
      led23.on();
      bot.sendMessage(chat_id, "LED encendido", "");
    }
    else if(text == "/led23Off"){ 
      led23.off();
      bot.sendMessage(chat_id, "LED apagado", "");
    }
    else if(text == "/led2On"){ 
      led2.on();
      bot.sendMessage(chat_id, "LED encendido", "");
    }
    else if(text == "/led2Off"){ 
      led2.off();
      bot.sendMessage(chat_id, "LED apagado", "");
    }
    else if(text == "/dht22"){
      float temperatura = dht22.readTemperature();
      float humedad = dht22.readHumidity();
      String mensaje = "Temperatura: " + String(temperatura) + " °C\nHumedad: " + String(humedad) + " %";
      bot.sendMessage(chat_id, mensaje, "");
    }
    else if(text == "/pote"){
      int valor_pote = pote.read();
      String mensaje = "El valor del potenciómetro es: " + String(valor_pote);
      bot.sendMessage(chat_id, mensaje, "");
    }
    else if(text == "/platiot"){
      float temperatura = dht22.readTemperature();
      float humedad = dht22.readHumidity();
      thingSpeakClient.sendData(temperatura, humedad);

      bot.sendMessage(chat_id, "Datos enviados a ThingSpeak.", "");
    }
    else if(text == "/displayLed23"){
      display.showLedStatus("LED Verde", led23.isOn());
    }
    else if(text == "/displayLed2"){
      display.showLedStatus("LED Azul", led2.isOn());
    }
    else if(text == "/displayDHT22"){
      float temperatura = dht22.readTemperature();
      float humedad = dht22.readHumidity();
      display.showDHT22Readings(temperatura, humedad);
    }
    else if(text == "/displayPote"){
      int valor_pote = pote.read();
      display.showPoteValue(valor_pote);
    }
    else if(text.startsWith("/display")){
      bot.sendMessage(chat_id, "Componente no reconocido.", "");
    }
    else{
      bot.sendMessage(chat_id, "Comando no reconocido. Envía /start para ver los comandos disponibles.", "");
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  display.begin();
  display.showLedStatus("Inicializando", true);

  previus = 0;
  Serial.print("Conectando a WiFi");
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi");
  secured_client.setInsecure();

  // ESTADO es : CONNECTED: OK
}

void loop() {

  if(millis() - previus > SCAN_TIME){ // Valida los segundos para volver a SCAN
    int n = bot.getUpdates(bot.last_message_received + 1);  // mensajes recibidos
    if(n >0){
      handleMessages(n);
    }
    previus = millis();
  }

}
