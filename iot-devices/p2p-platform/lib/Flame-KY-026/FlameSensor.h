#ifndef FLAME_SENSOR_KY_026_H
#define FLAME_SENSOR_KY_026_H

#include <Arduino.h>

class FlameSensor
{
private:
    int pin;         // Pin connected to the KY-026 sensor
    int alert_value; // Digital value that fire detected

public:
    // Constructor
    FlameSensor(int sensorPin, int alert_value);

    // Function to read sensor value
    int readValue();

    // Function to check if flame is detected
    bool isFlameDetected();
};

#endif // FLAME_SENSOR_KY_026_H