#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace Config {
    extern const char* DEVICE;
    extern const char* WIFI_SSID;
    extern const char* WIFI_PASSWORD;
    extern const char* INFLUXDB_URL;
    extern const char* INFLUXDB_TOKEN;
    extern const char* INFLUXDB_ORG;
    extern const char* INFLUXDB_BUCKET;
}

#endif // CONFIG_H
