// #include <ESP8266WiFi.h>
#include "WiFi.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHT_PIN 0
#define DHT_TYPE DHT22
#define FLAME_PIN 2

// WiFi settings
const char *ssid = "FSB-201";
// Replace with your WiFi name
const char *password = "123@123a";
// Replace with your WiFi password

// MQTT Broker settings
const char *mqtt_broker = "192.168.1.67";
// EMQX broker endpoint
const char *mqtt_topic = "test/topic";
// MQTT topic
const char *mqtt_username = "admin";
// MQTT username for authentication
const char *mqtt_password = "admin";
// MQTT password for authentication
const int mqtt_port = 1883;
// MQTT port (TCP)


class FlameSensor {
  private:
    int pin;

  public:
    // Constructor
    FlameSensor(int sensorPin) {
      pin = sensorPin;
      pinMode(pin, INPUT);
    }

    // Function to read sensor value
    int readValue() {
      return digitalRead(pin);
    }

    // Function to check if flame is detected
    bool isFlameDetected() {
      return (readValue() == HIGH);
    }
};

class DHT22Sensor {
  private:
    int pin;
    DHT dht;

  public:
    DHT22Sensor(int sensorPin) : pin(sensorPin), dht(sensorPin, DHT22) {
      dht.begin();
    }

    // Function to read humidity
    float readHumidity() {
      float humidity = dht.readHumidity();
      if (isnan(humidity)) {
        Serial.println("Failed to read humidity from DHT22 sensor!");
        return -1; // Return an error value
      }
      return humidity;
    }

    // Function to read temperature
    float readTemperature() {
      float temperature = dht.readTemperature();
      if (isnan(temperature)) {
        Serial.println("Failed to read temperature from DHT22 sensor!");
        return -1;
      }
      return temperature;
    }

    // Function to get both temperature and humidity at once
    bool readData(float &temperature, float &humidity) {
      humidity = readHumidity();
      temperature = readTemperature();

      if (humidity == -1 || temperature == -1) {
        return false;
      }
      return true;
    }
};

void connectToWiFi();

void connectToMQTTBroker();

void mqttCallback(char *topic, byte *payload, unsigned int length);

// Global objects
FlameSensor flame(0);
DHT22Sensor dht22(0);

// Wifi and MQTT
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

// Arduino Json
// https://arduinojson.org/v7/example/generator/
JsonDocument jsonDoc;

void initJsonDoc(){
  jsonDoc.clear();

  jsonDoc["name"] = "Nhom2_Node1";

  JsonArray jSensors = jsonDoc["sensors"].to<JsonArray>();
  jSensors.add("flame");
  jSensors.add("dht22");

  serializeJsonPretty(jsonDoc, Serial);
}

void setup() {
  Serial.begin(9600);

  // Create an instance of the FlameSensor class
  flame = FlameSensor(FLAME_PIN);

  // Create an instance of the DHT22Sensor class
  dht22 = DHT22Sensor(DHT_PIN);

  // Initialize json doc
  initJsonDoc();

  connectToWiFi();
  mqtt_client.setServer(mqtt_broker, mqtt_port);
  mqtt_client.setCallback(mqttCallback);
  if (!mqtt_client.connected()) {
    connectToMQTTBroker();
  }
}

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

char* convert() {
  // Calculate the size needed for the char array
  size_t size = measureJson(doc) + 1;  // +1 for the null terminator
}

void connectToMQTTBroker() {
  while (!mqtt_client.connected()) {
    String client_id = "esp8266-client-" + String(WiFi.macAddress());
    Serial.printf("Connecting to MQTT Broker as %s.....\n", client_id.c_str());
    if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
      mqtt_client.subscribe(mqtt_topic);

      String jsonString;
      serializeJsonPretty(jsonDoc, jsonString);

      mqtt_client.publish(mqtt_topic, toCharArray(jsonString));
      
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void collectData_FlameSensor() {

  JsonArray dataSeries = jsonDoc["data"]["flame"]["series"].to<JsonArray>();
  dataSeries.add(flame.readValue());

  // Read and print the sensor value
  Serial.print("Sensor Value: ");
  Serial.println(flame.readValue());

  // Check if flame is detected
  if (flame.isFlameDetected()) {
    Serial.println("Flame detected!");
  } else {
    Serial.println("No flame detected.");
  }
}

void collectData_DHT22Sensor() {
  float temperature, humidity;

  JsonArray dataTempSeries = jsonDoc["data"]["temperature"]["series"].to<JsonArray>();
  JsonArray dataHumiSeries = jsonDoc["data"]["humidity"]["series"].to<JsonArray>();

  // Read and print the temperature and humidity
  if (dht22.readData(temperature, humidity)) {
    dataTempSeries.add(temperature);
    dataHumiSeries.add(humidity);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read data from DHT22 sensor!");
  }
}

int loopCount = 0;

void loop() {
  delay(1000);

  collectData_FlameSensor();

  collectData_DHT22Sensor();

  if (++loopCount == 10) {
    if (!mqtt_client.connected()) {
      connectToMQTTBroker();
    }
    mqtt_client.loop();
    loopCount = 0;
  }
}
