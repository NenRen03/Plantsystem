#include "MoistureController.h"
#include <Arduino.h>


MoistureController::MoistureController(int moistPin, int pumpPin, int servoPin)
   :  servoController(servoPin) 
    {
    this->moistPin = moistPin;
    this->pumpPin = pumpPin;
    this->servoPin = servoPin;
    pinMode(pumpPin, OUTPUT);
}

void MoistureController::begin() {
    initialMoistValue = analogRead(moistPin);
    Serial.print("Intial Moisture Value = ");
    Serial.println(initialMoistValue);
}

void MoistureController::moistControl() {
    moistValue = analogRead(moistPin);
    moistDiff = initialMoistValue - moistValue;
    Serial.print("Moisture Value = ");
    Serial.println(moistDiff);

    if (initialMoistValue - moistValue >= 200) {
        pumpOn();
    } else {
        pumpOff();
    }
}

void MoistureController::pumpOn() {
    Serial.println("Pump is now on");
    digitalWrite(pumpPin, HIGH);
    servoController.servoOn();
    pumpStatus = true;
}

void MoistureController::pumpOff() {
    Serial.println("Pump is now off");
    digitalWrite(pumpPin, LOW);
    servoController.servoOff();
    pumpStatus = false;
}

int MoistureController::getMoistValue() {
    return moistValue;
}

bool MoistureController::getPumpStatus() {
    return pumpStatus;
}

bool MoistureController::getServoStatus() {
    return servoController.getServoStatus();
}