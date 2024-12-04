#include <dummy.h>

#include <WiFi.h>
#include "DHT.h"

// Wi-Fi credentials
const char *ssid = "Memo";      // Replace with your Wi-Fi network name
const char *password = "menna2917"; // Replace with your Wi-Fi password

// DHT11 Sensor Setup
#define DHTPIN 4     // D4 pin
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Dust Sensor Setup
#define DUSTPIN 34  // Dust sensor output pin (GPIO34)

// Hall Effect Sensor Setup
#define HALL_PIN 34 // Hall effect sensor output pin (GPIO34)
volatile unsigned long pulseCount = 0; // To count the pulses
unsigned long lastTime = 0; // To measure time intervals

void IRAM_ATTR countPulses() {
  pulseCount++; // Increment pulse count on each interrupt
}

void setup() {
  // Start Serial communication
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address assigned to the ESP32

  // Initialize the DHT sensor
  dht.begin();

  // Set up the Hall effect sensor pin as input
  pinMode(HALL_PIN, INPUT_PULLUP);
  
  // Attach an interrupt to the Hall effect sensor pin
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), countPulses, RISING);
}

void loop() {
  // Read and display DHT11 sensor data
  delay(2000); // Wait a few seconds between DHT measurements
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // In Celsius
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
  }

  // Read and display dust level
  int dustLevel = analogRead(DUSTPIN);
  Serial.print("Dust Level (Raw ADC Value): ");
  Serial.println(dustLevel); // Raw value from dust sensor

  // Measure frequency from Hall effect sensor every second
  if (millis() - lastTime >= 1000) {
    // Calculate frequency (pulses per second)
    unsigned long frequency = pulseCount; // Get the current pulse count
    pulseCount = 0; // Reset pulse count for the next interval
    lastTime = millis(); // Update lastTime

    // Print the frequency to the Serial Monitor
    Serial.print("Wind Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");
  }
}