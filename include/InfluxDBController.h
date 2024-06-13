#ifndef INFLUXDBCONTROLLER_H
#define INFLUXDBCONTROLLER_H

//include libraries
#include <Arduino.h>
#include <WiFiMulti.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <math.h>

//include own header files
#include "MoistureController.h"
#include "LightController.h"
#include "DHTController.h"
#include "config.h"

class InfluxDBController
{
private:
    const char* WIFI_SSID;
    const char* WIFI_PASSWORD;
    const char* DEVICE;
    const char* TZ_INFO = "CET-1CEST,M3.5.0,M10.5.0/3";

    String specificDateTimeUTC;

    WiFiMulti wifiMulti;
    InfluxDBClient client;
    Point deviceStatus;

    MoistureController &moistureController;
    LightController &lightController;
    DHTController &dhtController;

public:
    InfluxDBController(
        MoistureController& moisture,
        LightController& light,
        DHTController& dht
        );
    void begin();
    void sendData();
    // void deleteData(String specificDateTime);
};

#endif // INFLUXDBCONTROLLER_H
