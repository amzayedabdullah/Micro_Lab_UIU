#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Sensor and alert pins
const int sensorPin = A0;
const int Buzz = 7;
const int ledPin = 8;

// MQ2 Calibration constants
#define RL 10
#define m -0.263
#define b 0.42
#define Ro 20

// PPM threshold to trigger alert
#define GAS_THRESHOLD 3  // Set low for testing

void setup() {
  Serial.begin(9600);
  Serial.println("MQ2 warming up!");
  delay(20000); // MQ2 warm-up time

  pinMode(sensorPin, INPUT);
  pinMode(Buzz, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    while (true); // Stop if OLED fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("MQ2 Warming Up...");
  display.display();
  delay(2000);
}

void loop() {
  float sensorValue = analogRead(sensorPin);
  float VRL = sensorValue * (5.0 / 1023.0);
  float Rs = ((5.0 * RL) / VRL) - RL;
  float ratio = Rs / Ro;
  float ppm = pow(10, ((log10(ratio) - b) / m));

  Serial.print("PPM: ");
  Serial.println(ppm);

  // Hysteresis logic to stabilize alerts
  static bool alertOn = false;

  if (ppm > GAS_THRESHOLD + 0.5) {
    alertOn = true;
  } else if (ppm < GAS_THRESHOLD - 0.5) {
    alertOn = false;
  }

  // Control buzzer and LED
  digitalWrite(Buzz, alertOn ? HIGH : LOW);
  digitalWrite(ledPin, alertOn ? HIGH : LOW);

  // OLED Display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Gas Sensor MQ2");
  display.print("PPM: ");
  display.println(ppm, 2);

  display.setCursor(0, 30);
  if (alertOn) {
    display.println("!! GAS ALERT !!");
  } else {
    display.println("Status: SAFE");
  }

  display.display();

  delay(1000);
}
