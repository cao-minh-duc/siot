#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include <WiFi.h>

class WiFiModule {
private:
    const String ssid;
    const String password;
    unsigned long retryInterval;
    unsigned long lastAttemptTime;
    int maxRetries;
    int retryCount;
    bool offlineMode;

public:
    WiFiModule(const String ssid, const String password, unsigned long retryInterval = 5000, int maxRetries = 5);

    void connect();
    void handleConnection();
    bool isConnected();
    bool isOffline();
    void enterOfflineMode();
};

#endif
