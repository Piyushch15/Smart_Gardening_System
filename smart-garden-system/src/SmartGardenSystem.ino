#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2        // DHT11 sensor connected to pin 2
#define DHTTYPE DHT11   // Define sensor type
DHT dht(DHTPIN, DHTTYPE);

#define SOIL_MOISTURE_PIN A0  // Soil moisture sensor connected to A0
#define RELAY_PIN 7           // Relay module connected to pin 7

// Initialize LCD with I2C address (0x27 or 0x3F depending on your module)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(9600);
    dht.begin();
    lcd.init();  
    lcd.backlight(); 

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH); // Ensure pump is off at start

    lcd.setCursor(0, 0);
    lcd.print("Smart Garden");
    delay(2000);
    lcd.clear();
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
    int threshold = 700; // Adjust based on soil conditions

    // Handle sensor read errors
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        lcd.setCursor(0, 0);
        lcd.print("DHT Error!");
        delay(2000);
        return;
    }

    // Display readings on Serial Monitor
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print("C | Humidity: ");
    Serial.print(humidity);
    Serial.print("% | Moisture: ");
    Serial.println(soilMoistureValue);

    // Display temperature and humidity on first line
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temperature, 1); // 1 decimal place
    lcd.print(" Hum:");
    lcd.print(humidity, 0); // No decimal places
    lcd.print("% ");

    // Determine pump status
    bool pumpOn = soilMoistureValue > threshold;
    
    // Display soil moisture and pump status on second line
    lcd.setCursor(0, 1);
    lcd.print("Moist:");
    lcd.print(soilMoistureValue);
    lcd.print(" P:");
    lcd.print(pumpOn ? "ON " : "OFF");

    // Water Pump Control
    if (pumpOn) {
        Serial.println("Soil is dry! Pump ON");
        digitalWrite(RELAY_PIN, HIGH); // Activate pump
    } else {
        Serial.println("Soil is moist. Pump OFF");
        digitalWrite(RELAY_PIN, LOW); // Deactivate pump
    }

    delay(5000); // Wait for 5 seconds before updating again
}
