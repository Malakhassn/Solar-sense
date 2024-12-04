#include <Arduino.h>

#define HALL_PIN 34 // Hall effect sensor output pin (GPIO34)
volatile unsigned long pulseCount = 0; // To count the pulses
unsigned long lastTime = 0; // To measure time intervals

void IRAM_ATTR countPulses() {
  pulseCount++; // Increment pulse count on each interrupt
}

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud rate

  // Set up the Hall effect sensor pin as input
  pinMode(HALL_PIN, INPUT_PULLUP);

  // Attach an interrupt to the Hall effect sensor pin
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), countPulses, RISING);
}

void loop() {
  // Measure frequency every second
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