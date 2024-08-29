#include "PinManager.h"

PinManager::PinManager() : pinCount(0)
{
    // Constructor
}

void PinManager::addPin(const String &pinName, int port, int type)
{
    if (pinCount < MAX_PINS)
    {
        pinNames[pinCount] = pinName;
        pinInfos[pinCount] = {port, type};
        pinCount++;
    }
    else
    {
        Serial.println("Error: Pin limit reached.");
    }
}

PinInfo PinManager::getPin(const String &pinName)
{
    for (int i = 0; i < pinCount; i++)
    {
        if (pinNames[i] == pinName)
        {
            return pinInfos[i];
        }
    }
    return {-1, -1};
}

void PinManager::initPins()
{
    for (int i = 0; i < pinCount; i++)
    {
        pinMode(pinInfos[i].port, pinInfos[i].type);
    }
}

void PinManager::printPins()
{
    for (int i = 0; i < pinCount; i++)
    {
        Serial.print("PinName: ");
        Serial.print(pinNames[i]);
        Serial.print(", Port: ");
        Serial.print(pinInfos[i].port);
        Serial.print(", Type: ");
        Serial.println(pinInfos[i].type);
    }
}
