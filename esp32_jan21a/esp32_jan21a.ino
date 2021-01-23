#include <AsyncTCP.h>
#include <Adafruit_Sensor.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <ESPAsyncTCP.h>
#include <DHT.h>
#include <DHTesp.h>


// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

#define DHTPIN 27     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readTemp() {
  float t = dht.readTemperature();

  // here we check if there are any failed reads
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor");
    return "--";
  } else {
    Serial.println(t);
    return String(t);
  }
}

String readHum() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor");
    return "--";
  } else {
    Serial.println(h);
    return String(h);
  }
}
