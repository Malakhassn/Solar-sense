#include <WiFi.h>

const char *ssid = "Your_SSID";      // Replace with your Wi-Fi network name
const char *password = "Your_PASSWORD"; // Replace with your Wi-Fi password

void setup() {
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
}

void loop() {
  // You can add code here to handle data transfer or communication
}