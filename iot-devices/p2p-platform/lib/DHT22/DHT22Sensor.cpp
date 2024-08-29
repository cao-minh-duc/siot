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
        Serial.println("Failed to read humidity from DHT22 sensor!");
        return -1; // Return an error value
    }
    return humidity;
}

// Function to read temperature
float DHT22Sensor::readTemperature()
{
    float temperature = dht.readTemperature();
    if (isnan(temperature))
    {
        Serial.println("Failed to read temperature from DHT22 sensor!");
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
