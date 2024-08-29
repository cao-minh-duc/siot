#include <DHT.h>

#define RELAY_PIN_1 15
#define RELAY_PIN_2 2

#define DO_PIN 23  // ESP32's pin GPIO13 connected to DO pin of the flame sensor

// Define the pin where the DHT22 sensor is connected
#define DHTPIN 22     // Example: DHT22 is connected to digital pin 2

// Define the type of DHT sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302)

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);

  // initialize the ESP32's pin as an input
  pinMode(DO_PIN, INPUT);

  // Start the DHT sensor
  dht.begin();

  Serial.println("DHT22 sensor is ready");
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  digitalWrite(RELAY_PIN_1, HIGH);
  digitalWrite(RELAY_PIN_2, LOW);
  delay(500);
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_2, HIGH);

  int flame_state = digitalRead(DO_PIN);

  if (flame_state == LOW)
    Serial.println("No flame dected => The fire is NOT detected");
  else
    Serial.println("Flame dected => The fire is detected");

  // Read humidity (in %)
  float humidity = dht.readHumidity();

  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}
