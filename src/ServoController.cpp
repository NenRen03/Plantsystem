#include "ServoController.h"
#include <Arduino.h>

ServoController::ServoController(int servoPin){
    this->servoPin = servoPin;
    servo.attach(servoPin);
    servo.write(90);
}

void ServoController::servoOn() {
    servo.write(120);
   delay(340);

   servo.write(90);
   delay(250);

   servo.write(60);
   delay(600);

   servo.write(90);
   delay(250);

   servo.write(120);
   delay(340);

   servo.write(90);
   delay(250);

    servoStatus = true;
}

void ServoController::servoOff() {
    servo.write(90);
    servoStatus = false;
}

bool ServoController::getServoStatus() {
    return servoStatus;
}