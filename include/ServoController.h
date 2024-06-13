#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <Servo.h>

class ServoController {
private:
    Servo servo;
    int servoPin;
    bool servoStatus;

public:
    ServoController(int servoPin);

    void servoOn();
    void servoOff();
    bool getServoStatus();
};

#endif //SERVOCONTROLLER_H
