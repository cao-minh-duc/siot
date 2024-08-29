#include "DHT22Sensor.h"

// Constructor implementation
DHT22Sensor::DHT22Sensor(int sensorPin) : pin(sensorPin), dht(sensorPin, DHT22)
{
    dht.begin();
}

// Function to read humidity
float DHT22Sensor::readHumidity()
{
    float humidity = dht.readHumidity();
    if (isnan(humidity))
    {
        return -1;
    }
    return humidity;
}

// Function to read temperature
float DHT22Sensor::readTemperature()
{
    float temperature = dht.readTemperature();
    if (isnan(temperature))
    {
        return -1;
    }
    return temperature;
}

// Function to get both temperature and humidity at once
bool DHT22Sensor::readData(float &temperature, float &humidity)
{
    humidity = readHumidity();
    temperature = readTemperature();

    if (humidity == -1 || temperature == -1)
    {
        return false;
    }
    return true;
}

// Method to get the state as a JsonDocument
void DHT22Sensor::getState(JsonDocument &doc)
{
    float temperature, humidity;

    if (readData(temperature, humidity))
    {
        doc["temperature"] = temperature;
        doc["humidity"] = humidity;
    }
    else
    {
        doc["temperature"] = 0;
        doc["humidity"] = 0;
    }
}
