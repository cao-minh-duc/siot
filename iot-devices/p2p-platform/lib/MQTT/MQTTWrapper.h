#ifndef MQTT_WRAPPER_H
#define MQTT_WRAPPER_H

#include <PubSubClient.h>

class MQTTWrapper
{
private:
    const char *mqttServer;
    int mqttPort;
    const char *mqttUser;
    const char *mqttPassword;
    const char *clientId;

    PubSubClient client;

    unsigned long retryInterval;
    unsigned long lastAttemptTime;
    int maxRetries;
    int retryCount;
    bool offlineMode;

    void reconnect();

public:
    MQTTWrapper(Client &networkClient, const char *mqttServer, int mqttPort, const char *mqttUser, const char *mqttPassword, const char *clientId, unsigned long retryInterval = 5000, int maxRetries = 5);
    MQTTWrapper(Client &networkClient, const String mqttServer, int mqttPort, const String mqttUser, const String mqttPassword, const String clientId, unsigned long retryInterval = 5000, int maxRetries = 5);

    void setup();
    void handleConnection();
    bool isConnected();
    bool isOffline();
    void enterOfflineMode();
    void publish(const char *topic, const char *message);
    void publish(const String topic, const String message);
    void subscribe(const char *topic);
    void setCallback(MQTT_CALLBACK_SIGNATURE);
};

#endif
