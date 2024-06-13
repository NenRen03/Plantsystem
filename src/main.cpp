#include <Arduino.h>
#include "esp_task_wdt.h"
#include "LightController.h"
#include "DHTController.h"
#include "MoistureController.h"
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "InfluxDBController.h"

#define LIGHT_SENSOR_PIN 39
#define RF_PIN 25
#define LED_PIN 2
LightController lightController(LIGHT_SENSOR_PIN, RF_PIN, LED_PIN);

#define DHT_PIN 32
DHTController dhtController(DHT_PIN);

#define MOISTURE_PIN 36
#define PUMP_PIN 33
#define SERVO_PIN 13
MoistureController moistureController(MOISTURE_PIN, PUMP_PIN, SERVO_PIN);

InfluxDBController influxDBController(moistureController, lightController, dhtController); 

void setup(){
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();
    Serial.println("Program begun");
    influxDBController.begin();
    lightController.begin();
    dhtController.begin();
    moistureController.begin();
}

void loop(){
    Serial.println("Hello Minions");
    lightController.lightControl();
    dhtController.humidity();
    dhtController.temperature();
    moistureController.moistControl();
    //send data
    influxDBController.sendData();
}
