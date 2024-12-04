#include <DHT.h>
#include <WiFi.h>
#define DHTPIN 4 // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* server = "YOUR_WEB_APP_URL"; // Your Google Apps Script URL

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}
void loop() {
  // Read temperature and humidity from DHT11
  
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Placeholder values for air quality, dust concentration, and wind frequency
  float airQuality = 50; // Replace with actual sensor reading
  float dustConcentration = 30; // Replace with actual sensor reading
  float windFrequency = 1.5; // Replace with actual sensor reading

  if (!isnan(temperature) && !isnan(humidity)) {
   
    String url = String(server) + "?action=logData&temperature=" + temperature + "&humidity=" + humidity + "&airQuality=" + airQuality + "&dustConcentration=" + dustConcentration + "&windFrequency=" + windFrequency;
   
    WiFiClient client;
    if (client.connect(server, 80)) {
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + server + "\r\n" +
                   "Connection: close\r\n\r\n");
      delay(1000); // Wait for the response
      Serial.println("Data sent to Google Sheets");
    } else {
      Serial.println("Connection failed");
    }
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
  delay(30000); // Wait for 30 seconds before the next reading
}
