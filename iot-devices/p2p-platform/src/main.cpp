#include <Arduino.h>
#include <PinConfigure.h>
#include <DHT22Sensor.h>

// Initialize the DHT sensor
DHT22Sensor dht22Sensor(-1);

void setup()
{
  // Start Serial for debugging
  Serial.begin(115200);

  initPins();

  dht22Sensor = DHT22Sensor(getPin(PIN_22_INP_DHT22_01));
}

void loop()
{
  digitalWrite(getPin(PIN_02_OUT_RELAY_01), HIGH);
  digitalWrite(getPin(PIN_15_OUT_RELAY_02), LOW);
  delay(500);
  digitalWrite(getPin(PIN_02_OUT_RELAY_01), LOW);
  digitalWrite(getPin(PIN_15_OUT_RELAY_02), HIGH);

  int flame_state = digitalRead(getPin(PIN_23_INP_FLAME_01));

  if (flame_state == LOW)
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
  delay(2000);
}
