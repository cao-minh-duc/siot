// PinConfigure.h
#ifndef PINCONFIGURE_H
#define PINCONFIGURE_H

#include <Arduino.h>
#include <PinManager.h>

static const String PIN_02_OUT_RELAY_01 = "RELAY_01";
static const String PIN_15_OUT_RELAY_02 = "RELAY_02";
static const String PIN_22_INP_DHT22_01 = "DHT22_01";
static const String PIN_23_INP_FLAME_01 = "FLAME_01";

static PinManager pinManager;

void configurePins()
{
    // Add pins
    pinManager.addPin(PIN_02_OUT_RELAY_01, 02, OUTPUT);
    pinManager.addPin(PIN_15_OUT_RELAY_02, 15, OUTPUT);
    pinManager.addPin(PIN_22_INP_DHT22_01, 22, INPUT);
    pinManager.addPin(PIN_23_INP_FLAME_01, 23, INPUT);

    // Initialize pins
    pinManager.initPins();

    // Print all pins
    pinManager.printPins();
}

int getPin(const String &pinName)
{
    return pinManager.getPin(pinName).port;
}

#endif // PINCONFIGURE_H
