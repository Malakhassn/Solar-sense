#include "DHT.h"

// Define the pin where the DHT11 is connected
#define DHTPIN 4     // D4 pin

// Define the type of DHT sensor
#define DHTTYPE DHT11   // DHT 11

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the Serial communication
  Serial.begin(115200);
  
  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // In Celsius

  // Check if any reads failed and exit early (to try again).
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
  Serial.println(" *C");
}
