#include "LightController.h"
#include <Arduino.h>
#include "switchKaKu.h"

#define TRANSMITTERID1 060730

LightController::LightController(int ldrPin, int rfPin, int ledPin) {
    this->ldrPin = ldrPin;
    this->rfPin = rfPin;
    this->ledPin = ledPin;
    pinMode(ldrPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void LightController::begin() {
    initialLightValue = analogRead(ldrPin);
    Serial.print("Initial Light Value = ");
    Serial.println(initialLightValue);
}

void LightController::lightControl() {
    lightValue = analogRead(ldrPin);
    Serial.print("Light Value = ");
    Serial.println(lightValue);

    if (initialLightValue - lightValue >= 200) {
        lampOn();
        digitalWrite(ledPin, HIGH);
    } else {
        lampOff();
        digitalWrite(ledPin, LOW);
    }
}

void LightController::lampOn() {
    switchKaku(rfPin, TRANSMITTERID1, 1, 1, true, 3);
    Serial.println("Lamp is on");
    lampStatus = true;
}

void LightController::lampOff() {
    switchKaku(rfPin, TRANSMITTERID1, 1, 1, false, 3);
    Serial.println("Lamp is off");
    lampStatus = false;
}

int LightController::getLightValue() {
    return lightValue;
}

bool LightController::getLampStatus() {
    return lampStatus;
}
