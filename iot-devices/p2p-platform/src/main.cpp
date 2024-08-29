#include <Arduino.h>
#include <DHT22Sensor.h>
#include <FlameSensor.h>
#include <RelayModule.h>
#include <PinConfigure.h>
#include <TaskConfigure.h>

// Initialize modules
DHT22Sensor dht22Sensor(-1);
FlameSensor flameSensor(-1, -1);
RelayModule relayModule_01(-1);
RelayModule relayModule_02(-1);

// TaskScheduler
Scheduler runner;

void setup()
{
  // Start Serial for debugging
  Serial.begin(115200);

  // Configure Pins for modules and initialize manager
  configurePins();

  dht22Sensor = DHT22Sensor(getPin(PIN_22_INP_DHT22_01));
  flameSensor = FlameSensor(getPin(PIN_23_INP_FLAME_01), LOW);
  relayModule_01 = RelayModule(getPin(PIN_02_OUT_RELAY_01));
  relayModule_02 = RelayModule(getPin(PIN_15_OUT_RELAY_02));

  relayModule_01.begin();
  relayModule_02.begin();

  // Configure Tasks
  configureTasks();
}

void loop()
{
  runner.execute();
}

// Implements tasks

void storeState_FlameSensor()
{
  if (flameSensor.isFlameDetected())
    Serial.println("No flame dected => The fire is NOT detected");
  else
    Serial.println("Flame dected => The fire is detected");
}

void storeState_DHTSensor()
{
  float temperature, humidity;

  if (dht22Sensor.readData(temperature, humidity))
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  else
  {
    Serial.println("Failed to read from DHT22 sensor.");
  }
}

void storeState_Relays()
{
  relayModule_01.toggle();
  relayModule_02.toggle();

  Serial.println("Relay 1: " + String(relayModule_01.isOn() ? "ON" : "OFF"));
  Serial.println("Relay 2: " + String(relayModule_02.isOn() ? "ON" : "OFF"));
}