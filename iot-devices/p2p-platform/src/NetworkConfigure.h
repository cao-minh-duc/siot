#ifndef NETWORK_CONFIGURE_H
#define NETWORK_CONFIGURE_H

#include <Arduino.h>

static String SIOT_CLIENT_ID = "DEFAULT_MEMBER";

static const String WIFI_SSID = "VH True Farm";
static const String WIFI_PSWD = "nuocdaongman";

// static const String WIFI_SSID = "'Tuanboy '";
// static const String WIFI_PSWD = "zenvy123";

// static const String WIFI_SSID = "FSB-201";
// static const String WIFI_PSWD = "123@123a";

// static const String WIFI_SSID = "186DoanKhue";
// static const String WIFI_PSWD = "0905183186";
static const unsigned long WIFI_RETRY_INTERVAL = 20000;

static const String MQTT_SERVER = "ec2-13-250-41-157.ap-southeast-1.compute.amazonaws.com";
static const String MQTT_SERVER_IP = "91.121.93.94";
static const int MQTT_PORT = 1883;
static const String MQTT_USER = "admin";
static const String MQTT_PSWD = "admin";
static const unsigned long MQTT_RETRY_INTERVAL = 10000;

#endif // NETWORK_CONFIGURE_H
