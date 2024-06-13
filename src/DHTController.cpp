#include "DHTController.h"
#include <Arduino.h>

DHTController::DHTController(int pin) : pin(pin), dht(pin, DHTTYPE) {
    Serial.println(F("DHT11 test!"));
}

void DHTController::begin() {
    dht.begin();
}

int DHTController::humidity() {
    float h = dht.readHumidity();
    if (isnan(h)) {
        Serial.println(F("Failed to read humidity!"));
        return -1;
    }
    Serial.print(F("Humidity: "));
    Serial.print(h);
    return (int)h;
}

int DHTController::temperature() {
    float t = dht.readTemperature();
    if (isnan(t)) {
        Serial.println(F("Failed to read temperature!"));
        return -1;
    }
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.println("°C");
    return (int)t;
}
