#include "RelayModule.h"

// Constructor to initialize the relay pin
RelayModule::RelayModule(int pin) : relayPin(pin), isRelayOn(false) {}

// Method to initialize the relay
void RelayModule::begin()
{
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW); // Ensure the relay starts in the off state
}

// Method to turn the relay on
void RelayModule::turnOn()
{
    digitalWrite(relayPin, HIGH);
    isRelayOn = true;
}

// Method to turn the relay off
void RelayModule::turnOff()
{
    digitalWrite(relayPin, LOW);
    isRelayOn = false;
}

// Method to toggle the relay status
void RelayModule::toggle()
{
    if (isRelayOn)
    {
        turnOff();
    }
    else
    {
        turnOn();
    }
}

// Method to get the current status of the relay
bool RelayModule::isOn()
{
    return isRelayOn;
}
