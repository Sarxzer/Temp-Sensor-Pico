#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <LM75A.h>


// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define SDA_PIN 20
#define SCL_PIN 21

TwoWire myWire(i2c0, SDA_PIN, SCL_PIN);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &myWire, -1); 

Generic_LM75_11Bit temperature;

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging at 115200 baud
  delay(1000); // Wait for serial to initialize

  // Initialize I2C communication with custom SDA and SCL pins
  myWire.setSDA(SDA_PIN);
  myWire.setSCL(SCL_PIN);
  myWire.begin();

  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("OLED Initialized");
  display.display();

  temperature.

  delay(2000); // Wait for 2 seconds to show the initialization message
  // Scan I2C devices
  display.clearDisplay();
  Serial.println("Scanning I2C devices...");
  display.setCursor(0, 0);
  display.println("I2C Scan:");
  for (uint8_t address = 1; address < 127; address++) {
    myWire.beginTransmission(address);
    if (myWire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
      display.setCursor(0, 10 + (address * 2));
      display.print("0x");
      display.println(address, HEX);
    }
  }
  display.display();

  delay(5000); // Wait for a second before clearing the display

  // Initialize the temperature sensor
  if (!temperature.readTemperatureC()) {
    display.setCursor(0, 10);
    display.print("Temp Sensor Err");
    display.display();
    while (1);
  }
}

void loop() {
  float temperatureC = temperature.readTemperatureC();
  display.setCursor(0, 20);
  display.print("Temp: ");
  display.print(temperatureC);
  display.print(" C");
  display.display();
  delay(1000);
}