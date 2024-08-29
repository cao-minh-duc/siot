#include <Arduino.h>
#include "FlameSensor.h"

// Constructor implementation
FlameSensor::FlameSensor(int sensorPin, int alert) : pin(sensorPin), alert_value(alert)
{
    pinMode(pin, INPUT);
}

// Function to read sensor value
int FlameSensor::readValue()
{
    return digitalRead(pin);
}

// Function to check if flame is detected
bool FlameSensor::isFlameDetected()
{
    return (readValue() == alert_value);
}