#include "InfluxDBController.h"
#include "config.h"
#include <Arduino.h> 

#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

InfluxDBController::InfluxDBController(
    MoistureController& moisture,
    LightController& light,
    DHTController& dht
    )
    : WIFI_SSID(Config::WIFI_SSID), WIFI_PASSWORD(Config::WIFI_PASSWORD), DEVICE(Config::DEVICE),
      client(Config::INFLUXDB_URL, Config::INFLUXDB_ORG, Config::INFLUXDB_BUCKET, Config::INFLUXDB_TOKEN, InfluxDbCloud2CACert),
      deviceStatus("devices"),
      moistureController(moisture),
      lightController(light),
      dhtController(dht)

{}
void InfluxDBController::begin()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to wifi....");
    while (wifiMulti.run() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    client.setWriteOptions(WriteOptions().batchSize(1).flushInterval(0));

    deviceStatus.addTag("device", DEVICE);
    deviceStatus.addTag("SSID", WiFi.SSID());

    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

    if (client.validateConnection())
    {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(client.getServerUrl());
    }
    else
    {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(client.getLastErrorMessage());
    }
}


void InfluxDBController::sendData()
{
    deviceStatus.clearFields();
    
    //send device data
    int t_f = temprature_sens_read();
    int t_c = (t_f - 32) * 5 / 9;
    deviceStatus.addField("internal_temp", t_c);

    int wifiStrength = WiFi.RSSI();
    deviceStatus.addField("wifi_strength", wifiStrength);

    unsigned long uptime = millis() / 1000;
    deviceStatus.addField("uptime", uptime);

    //Retrieve sensor/actor data
    int temperature = dhtController.temperature();
    int humidity = dhtController.humidity();
    int ldr = lightController.getLightValue();
    int moisture = moistureController.getMoistValue();
    bool pumpOn = moistureController.getPumpStatus();
    bool lampOn = lightController.getLampStatus();
    bool servoOn = moistureController.getServoStatus();
    
    //send sensor/actor data
    deviceStatus.addField("temprature", temperature);
    deviceStatus.addField("humidity", humidity);
    deviceStatus.addField("moisture", moisture);
    deviceStatus.addField("ldr", ldr);
    deviceStatus.addField("lampOn", lampOn ? 1 : 0);
    deviceStatus.addField("pumpOn", pumpOn ? 1 : 0);
    deviceStatus.addField("servoOn", servoOn ? 1 : 0);

    if (wifiMulti.run() != WL_CONNECTED)
    {
        Serial.println("Wifi connection lost");
    }

    if (!client.writePoint(deviceStatus))
    {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    }

    Serial.println("Wait 1s");
    delay(1000);
}

// void InfluxDBController::deleteData(String specificDateTime)
// {
//     specificDateTimeUTC = specificDateTime;
//     String bucketStr = String(INFLUXDB_BUCKET);

//     String query = "from(bucket: \"" + bucketStr + "\") \
//             |> range(start: 0, stop: -1h) \
//             |> filter(fn: (r) => r._measurement == \"wifi_status\" and r._time < " + specificDateTimeUTC + ") \
//             |> delete()";

//     Serial.print("Deleting data with query: ");
//     Serial.println(query);

//     FluxQueryResult result = client.query(query);

//     if (result.getError() != "")
//     {
//         Serial.print("Query result error: ");
//         Serial.println(result.getError());
//     }
//     else
//     {
//         Serial.println("Data deletion successful!");
//     }

//     result.close();

//     Serial.println("Wait 10s");
//     delay(10000);
// }
