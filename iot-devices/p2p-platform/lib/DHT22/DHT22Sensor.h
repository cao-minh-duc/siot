#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

#include <DHT.h>
#include <ArduinoJson.h>

class DHT22Sensor
{
private:
    int pin; // Pin connected to the DHT22 sensor
    DHT dht; // DHT object for sensor interaction

public:
    // Constructor
    DHT22Sensor();
    DHT22Sensor(int sensorPin);

    // Function to read humidity
    float readHumidity();

    // Function to read temperature
    float readTemperature();

    // Function to get both temperature and humidity at once
    bool readData(float &temperature, float &humidity);

    // Method to get the state as a JsonDocument
    void getState(JsonDocument &doc);
};

#endif // DHT22SENSOR_H
