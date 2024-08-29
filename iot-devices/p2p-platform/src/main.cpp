#include <Arduino.h>
#include <DHT22Sensor.h>
#include <FlameSensor.h>
#include <RelayModule.h>
#include <WiFiModule.h>
#include <MQTTWrapper.h>
#include <PinConfigure.h>
#include <StateStorage.h>
#include <NetworkConfigure.h>
#include <TaskConfigure.h>
#include <UUID.h>

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
WiFiClient wifiClient;
WiFiModule wifi(WIFI_SSID, WIFI_PSWD, WIFI_RETRY_INTERVAL);
MQTTWrapper mqtt(wifiClient, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PSWD, SIOT_CLIENT_ID);

void setup()
{
  // Start Serial for debugging
  Serial.begin(115200);

  // Config Unique Id for client
  UUID uuid;
  uuid.generate();
  SIOT_CLIENT_ID = uuid.toCharArray();

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

  // Connect to WiFi
  wifi.connect();

  // Setup MQTT
  mqtt.setup();
  mqtt.setCallback([](char *topic, byte *payload, unsigned int length)
                   {
                    Serial.print("Message arrived in topic: ");
                    Serial.println(topic);

                    Serial.print("Message:");
                    for (int i = 0; i < length; i++) {
                        Serial.print((char)payload[i]);
                    }
                    Serial.println();
                    Serial.println("-----------------------"); });
}

void loop()
{
  runner.execute();
}

#pragma region Implement Tasks

void network_CheckWiFiConnection()
{
  if (wifi.isOffline())
  {
    tNetwork_CheckWiFiConnection.disable();
    return;
  }
  wifi.handleConnection();
}

void network_CheckMQTTConnection()
{
  if (mqtt.isOffline())
  {
    tNetwork_CheckMQTTConnection.disable();
    return;
  }
  mqtt.handleConnection();
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

void network_PublishStatisticData()
{
  String serializedState = stateStorage.serializeStorage();
  try
  {
    if (mqtt.isConnected())
    {
      mqtt.publish("test/topic", serializedState);
      Serial.println("Message published");
    }
  }
  catch (const std::exception &e)
  {
    Serial.println(e.what());
  }

  // Clear the state after logging
  stateStorage.clearStorage();
}

#pragma endregion Implement Tasks
