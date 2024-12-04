#include <Arduino.h>

#define DUSTPIN 34  // Dust sensor output pin (GPIO34)

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud rate
}

void loop() {
  // Read dust level from the GP2Y1014AU0F
  int dustLevel = analogRead(DUSTPIN);
  
  // Print the dust level to the Serial Monitor
  Serial.print("Dust Level (Raw ADC Value): ");
  Serial.println(dustLevel); // Raw value from dust sensor

  // Optional: Convert the raw value to a more interpretable value (if needed)
  // For example, you might want to scale the value or convert it to a concentration
  // This part is sensor-specific and may require calibration.

  delay(2000); // Wait for 2 seconds before the next reading
}