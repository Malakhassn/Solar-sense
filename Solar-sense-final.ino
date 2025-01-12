#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

#define DHTPIN 4          // DHT11 data pin
#define DHTTYPE DHT11     // DHT 11
#define DUSTPIN 34        // GP2Y1014AU0F analog pin
#define HALL_A_PIN 34     // Hall Encoder Output A
#define HALL_B_PIN 35     // Hall Encoder Output B
#define HALL_INDEX_PIN 32  // Hall Encoder Index
#define HALL_ENABLE_PIN 33 // Hall Encoder Enable

DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "Memo"; // Your WiFi SSID
const char* password = "menna2917"; // Your WiFi Password
const String googleSheetURL = "https://drive.google.com/drive/u/2/folders/1dK9FkBMcz1WXwew6KEULHapOlF74G26Y"; // Your Google Sheets URL

volatile int windFrequency = 0; // Variable to store wind frequency
unsigned long lastMeasurementTime = 0;

void IRAM_ATTR hallISR() {
  windFrequency++; // Increment frequency count on each interrupt
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Hall Encoder Setup
  pinMode(HALL_A_PIN, INPUT);
  pinMode(HALL_B_PIN, INPUT);
  pinMode(HALL_INDEX_PIN, INPUT);
  pinMode(HALL_ENABLE_PIN, OUTPUT);
  digitalWrite(HALL_ENABLE_PIN, HIGH); // Enable the encoder
  attachInterrupt(digitalPinToInterrupt(HALL_A_PIN), hallISR, RISING); // Attach interrupt

  // WiFi Connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Read Dust Sensor
  int dustValue = analogRead(DUSTPIN);
  float dustConcentration = (dustValue / 1024.0) * 5.0; // Example conversion

  // Check thresholds
  if (temperature > 45 || humidity < 30 || dustConcentration > 10 || windFrequency > 17) {
    sendWhatsAppNotification();
  }

  // Send data to Google Sheets every 30 seconds
  if (millis() - lastMeasurementTime > 30000) {
    sendDataToGoogleSheets(temperature, humidity, dustConcentration, windFrequency);
    lastMeasurementTime = millis();
    windFrequency = 0; // Reset wind frequency count after sending
  }

  delay(1000); // Short delay to avoid overwhelming the loop
}

void sendWhatsAppNotification() {
  String url = "https://api.callmebot.com/whatsapp.php?phone=01069173186=Alert! Values exceeded limits.";
  
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
            Serial.print("WhatsApp notification sent, response code: ");
        Serial.println(httpResponseCode);
    } else {
        Serial.print("Error sending WhatsApp notification: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
    }

  http.end();
}

void sendDataToGoogleSheets(float temperature, float humidity, float dust, int windFrequency) {
  String url = googleSheetURL + "?temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&dust=" + String(dust) + "&windFrequency=" + String(windFrequency);
  
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
     Serial.print("Data sent to Google Sheets, response code: ");
        Serial.println(httpResponseCode);
    } else {
        Serial.print("Error sending data to Google Sheets: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
    }
     http.end();
}