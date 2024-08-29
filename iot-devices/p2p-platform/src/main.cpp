#include <Arduino.h>
#include <PinConfigure.h>
#include <DHT22Sensor.h>
#include <FlameSensor.h>
#include <RelayModule.h>

// Initialize the DHT sensor
DHT22Sensor dht22Sensor(-1);
FlameSensor flameSensor(-1, -1);
RelayModule relayModule_01(-1);
RelayModule relayModule_02(-1);

void setup()
{
  // Start Serial for debugging
  Serial.begin(115200);

  initPins();

  dht22Sensor = DHT22Sensor(getPin(PIN_22_INP_DHT22_01));
  flameSensor = FlameSensor(getPin(PIN_23_INP_FLAME_01), LOW);
  relayModule_01 = RelayModule(getPin(PIN_02_OUT_RELAY_01));
  relayModule_02 = RelayModule(getPin(PIN_15_OUT_RELAY_02));

  relayModule_01.begin();
  relayModule_02.begin();
}

void loop()
{
  relayModule_01.turnOn();
  relayModule_02.turnOff();
  delay(500);
  relayModule_01.turnOff();
  relayModule_02.turnOn();

  if (flameSensor.isFlameDetected())
    Serial.println("No flame dected => The fire is NOT detected");
  else
    Serial.println("Flame dected => The fire is detected");

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

  // Wait a few seconds between measurements
  delay(1000);
}
