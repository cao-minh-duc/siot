#include "WiFiModule.h"

// Constructor to initialize with SSID, password, retry interval, and max retries
WiFiModule::WiFiModule(const String ssid, const String password, unsigned long retryInterval, int maxRetries)
    : ssid(ssid), password(password), retryInterval(retryInterval), lastAttemptTime(0),
      maxRetries(maxRetries), retryCount(0), offlineMode(false) {}

// Method to initiate the connection to WiFi
void WiFiModule::connect()
{
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    retryCount = 0;      // Reset retry count after successful connection
    offlineMode = false; // Ensure offline mode is disabled
}

// Method to handle connection and retry if disconnected
void WiFiModule::handleConnection()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    unsigned long currentMillis = millis();
    if (currentMillis - lastAttemptTime >= retryInterval)
    {
        retryCount++;
        Serial.print("WiFi disconnected. Attempting to reconnect... (Attempt ");
        Serial.print(retryCount);
        Serial.println(")");

        lastAttemptTime = currentMillis;

        if (retryCount <= maxRetries)
        {
            WiFi.begin(ssid, password);
        }
        else
        {
            enterOfflineMode();
        }
    }
}

// Method to check if WiFi is connected
bool WiFiModule::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

// Method to check if the device is in offline mode
bool WiFiModule::isOffline()
{
    return offlineMode;
}

// Method to enter offline mode after exceeding retry attempts
void WiFiModule::enterOfflineMode()
{
    Serial.println("Unable to connect to WiFi after multiple attempts. Entering Offline Mode.");
    offlineMode = true;
    WiFi.disconnect(true); // Optionally, disconnect WiFi
}
