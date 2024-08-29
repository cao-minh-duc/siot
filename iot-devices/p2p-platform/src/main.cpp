#include <Arduino.h>
#include <DHT22Sensor.h>
#include <FlameSensor.h>
#include <RelayModule.h>
#include <WiFiModule.h>
#include <PinConfigure.h>
#include <StateStorage.h>
#include <NetworkConfigure.h>
#include <TaskConfigure.h>

// Initialize modules
DHT22Sensor dht22Sensor(-1);
FlameSensor flameSensor(-1, -1);
RelayModule relayModule_01(-1);
RelayModule relayModule_02(-1);

// State Storage with dynamic capacity
StateStorage stateStorage(4096); // Adjust based on expected JSON size

// TaskScheduler
Scheduler runner;

// Create a WiFiWrapper instance
WiFiModule wifi(WIFI_SSID, WIFI_PSWD, WIFI_RETRY_INTERVAL);

void setup()
{
  // Start Serial for debugging
  Serial.begin(115200);

  // Configure Pins for modules and initialize manager
  configurePins();

  dht22Sensor = DHT22Sensor(getPin(PIN_22_INP_DHT22_01));
  flameSensor = FlameSensor(getPin(PIN_23_INP_FLAME_01), HIGH);
  relayModule_01 = RelayModule(getPin(PIN_02_OUT_RELAY_01));
  relayModule_02 = RelayModule(getPin(PIN_15_OUT_RELAY_02));

  relayModule_01.begin();
  relayModule_02.begin();

  // Configure Tasks
  configureTasks();

  // Connect tot WiFi
  wifi.connect();
}

void loop()
{
  runner.execute();
}

#pragma region Implement Tasks

void network_CheckConnection()
{
  if (wifi.isOffline())
  {
    tNetwork_CheckConnection.disable();
    return;
  }
  wifi.handleConnection();
}

void storeState_FlameSensor()
{
  JsonDocument flameState;
  flameSensor.getState(flameState);
  stateStorage.addState(PIN_23_INP_FLAME_01.c_str(), flameState);
}

void storeState_DHTSensor()
{
  JsonDocument dhtState;
  dht22Sensor.getState(dhtState);
  stateStorage.addState(PIN_22_INP_DHT22_01.c_str(), dhtState);
}

void storeState_Relays()
{
  relayModule_01.toggle();
  relayModule_02.toggle();

  JsonDocument relay_01, relay_02;

  relayModule_01.getState(relay_01);
  stateStorage.addState(PIN_02_OUT_RELAY_01.c_str(), relay_01);

  relayModule_01.getState(relay_02);
  stateStorage.addState(PIN_15_OUT_RELAY_02.c_str(), relay_02);
}

void logAndClearState()
{
  String serializedState = stateStorage.serializeStorage();
  Serial.println("Serialized State:");
  Serial.println(serializedState);

  // Clear the state after logging
  stateStorage.clearStorage();
}

#pragma endregion Implement Tasks
