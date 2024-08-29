#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class RelayModule
{
private:
    int relayPin;
    bool isRelayOn;

public:
    // Constructor to initialize the relay pin
    RelayModule(int pin);

    // Method to initialize the relay
    void begin();

    // Method to turn the relay on
    void turnOn();

    // Method to turn the relay off
    void turnOff();

    // Method to toggle the relay status
    void toggle();

    // Method to get the current status of the relay
    bool isOn();

    // Method to get the state as a JsonDocument
    void getState(JsonDocument &doc);
};

#endif
