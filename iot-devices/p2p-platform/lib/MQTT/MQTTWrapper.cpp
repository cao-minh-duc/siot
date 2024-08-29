#include "MQTTWrapper.h"

// Constructor to initialize with MQTT server, port, credentials, retry settings, and a network client
MQTTWrapper::MQTTWrapper(Client &networkClient, const char *mqttServer, int mqttPort, const char *mqttUser, const char *mqttPassword, const char *clientId, unsigned long retryInterval, int maxRetries)
    : mqttServer(mqttServer), mqttPort(mqttPort), mqttUser(mqttUser), mqttPassword(mqttPassword), clientId(clientId),
      client(networkClient), retryInterval(retryInterval), lastAttemptTime(0),
      maxRetries(maxRetries), retryCount(0), offlineMode(false) {}
MQTTWrapper::MQTTWrapper(Client &networkClient, const String mqttServer, int mqttPort, const String mqttUser, const String mqttPassword, const String clientId, unsigned long retryInterval, int maxRetries)
    : mqttServer(mqttServer.c_str()), mqttPort(mqttPort), mqttUser(mqttUser.c_str()), mqttPassword(mqttPassword.c_str()), clientId(clientId.c_str()),
      client(networkClient), retryInterval(retryInterval), lastAttemptTime(0),
      maxRetries(maxRetries), retryCount(0), offlineMode(false) {}
// Setup MQTT connection settings
void MQTTWrapper::setup()
{
    client.setServer(mqttServer, mqttPort);
}

// Method to handle connection and retry if disconnected
void MQTTWrapper::handleConnection()
{
    if (!client.connected())
    {
        unsigned long currentMillis = millis();
        if (currentMillis - lastAttemptTime >= retryInterval)
        {
            retryCount++;
            Serial.print("MQTT disconnected. Attempting to reconnect... (Attempt ");
            Serial.print(retryCount);
            Serial.println(")");

            lastAttemptTime = currentMillis;

            if (retryCount <= maxRetries)
            {
                reconnect();
            }
            else
            {
                enterOfflineMode();
            }
        }
    }
    else
    {
        client.loop();
    }
}

// Method to check if MQTT is connected
bool MQTTWrapper::isConnected()
{
    return client.connected();
}

// Method to check if the device is in offline mode
bool MQTTWrapper::isOffline()
{
    return offlineMode;
}

// Method to enter offline mode after exceeding retry attempts
void MQTTWrapper::enterOfflineMode()
{
    Serial.println("Unable to connect to MQTT broker after multiple attempts. Entering Offline Mode.");
    offlineMode = true;
}

// Reconnect method to handle the MQTT reconnection process
void MQTTWrapper::reconnect()
{
    if (!client.connected())
    {
        Serial.print("Connecting to MQTT broker...");
        if (client.connect(clientId, mqttUser, mqttPassword))
        {
            Serial.println("connected!");
            retryCount = 0;      // Reset retry count after successful connection
            offlineMode = false; // Ensure offline mode is disabled
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in a few seconds");
        }
    }
}

// Method to publish a message to a topic
void MQTTWrapper::publish(const char *topic, const char *message)
{
    if (client.connected())
    {
        client.publish(topic, message);
    }
}

// Method to publish a message to a topic
void MQTTWrapper::publish(const String topic, const String message)
{
    publish(topic.c_str(), message.c_str());
}

// Method to subscribe to a topic
void MQTTWrapper::subscribe(const char *topic)
{
    if (client.connected())
    {
        client.subscribe(topic);
    }
}

// Method to set a callback function for incoming messages
void MQTTWrapper::setCallback(MQTT_CALLBACK_SIGNATURE)
{
    client.setCallback(callback);
}
