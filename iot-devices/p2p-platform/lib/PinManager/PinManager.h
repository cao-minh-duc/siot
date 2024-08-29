#ifndef PINMANAGER_H
#define PINMANAGER_H

#include <Arduino.h>

#define MAX_PINS 10

// Define a structure to hold pin information
struct PinInfo
{
    int port;
    int type;
};

// Define the PinManager class
class PinManager
{
public:
    PinManager();
    void addPin(const String &pinName, int port, int type);
    PinInfo getPin(const String &pinName);
    void initPins();
    void printPins();

private:
    String pinNames[MAX_PINS];
    PinInfo pinInfos[MAX_PINS];
    int pinCount;
};

#endif // PINMANAGER_H
