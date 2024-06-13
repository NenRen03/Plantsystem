#ifndef DHTCONTROLLER_H
#define DHTCONTROLLER_H

#include "DHT.h"

#define DHTTYPE DHT11

class DHTController
{
private:
    int pin;
    DHT dht;

public:
    DHTController(int pin);
    void begin();
    int humidity();
    int temperature();
};

#endif // DHTCONTROLLER_H
