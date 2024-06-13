#include "ServoController.h"
#include <Arduino.h>

ServoController::ServoController(int servoPin){
    this->servoPin = servoPin;
    servo.attach(servoPin);
    servo.write(90);
}

void ServoController::servoOn() {
   servo.write(100);
   delay(1150);

   servo.write(90);
   delay(500);

   servo.write(80);
   delay(1350);

   servo.write(90);
   delay(500);

   servo.write(100);
   delay(1150);

   servo.write(90);
   delay(500);

    servoStatus = true;
}

void ServoController::servoOff() {
    servo.write(90);
    servoStatus = false;
}

bool ServoController::getServoStatus() {
    return servoStatus;
}