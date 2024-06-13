#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

class LightController
{
private:
    int ldrPin;
    int rfPin;
    int ledPin;
    int initialLightValue;
    int lightValue;
    bool lampStatus;

public:
    LightController(int ldrPin, int rfPin, int ledPin);
    void begin();
    void lightControl();
    void lampOn();
    void lampOff();
    int getLightValue();
    bool getLampStatus();
};

#endif // LIGHTCONTROLLER_H

