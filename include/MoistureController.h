#ifndef MOISTURECONTROLLER_H
#define MOISTURECONTROLLER_H

#include "ServoController.h"

class MoistureController
{
private:
    int moistPin;
    int initialMoistValue;
    int moistValue;
    int moistDiff;
    
    int pumpPin;
    bool pumpStatus;

    ServoController servoController;
    int servoPin;

public:
    MoistureController(int moistPin, int pumpPin, int servoPin);
    void begin();
    void moistControl();
    void pumpOn();
    void pumpOff();
    int getMoistValue();
    bool getPumpStatus();
    bool getServoStatus();
};

#endif // MOISTURECONTROLLER_H
