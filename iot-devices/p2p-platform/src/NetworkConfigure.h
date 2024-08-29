#ifndef NETWORK_CONFIGURE_H
#define NETWORK_CONFIGURE_H

#include <Arduino.h>

static String SIOT_CLIENT_ID = "DEFAULT_MEMBER";

// static const String WIFI_SSID = "FSB-201";
// static const String WIFI_PSWD = "123@123a";

static const String WIFI_SSID = "186DoanKhue";
static const String WIFI_PSWD = "xxxxxxxxxxx";
static const unsigned long WIFI_RETRY_INTERVAL = 20000;

static const String MQTT_SERVER = "ec2-13-250-41-157.ap-southeast-1.compute.amazonaws.com";
static const int MQTT_PORT = 1883;
static const String MQTT_USER = "admin";
static const String MQTT_PSWD = "admin";
static const unsigned long MQTT_RETRY_INTERVAL = 20000;

#endif // NETWORK_CONFIGURE_H
