#include <ESP8266WiFi.h>

#define S0 D3
#define S1 D4
#define S2 D5
#define S3 D6
#define sensorOut D7

void setup() {
  // Set pin modes
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(115200);
}

void loop() {
  // Select red filter
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int redFrequency = pulseIn(sensorOut, LOW);

  // Select green filter
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int greenFrequency = pulseIn(sensorOut, LOW);

  // Select blue filter
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int blueFrequency = pulseIn(sensorOut, LOW);

  // Print the color frequencies
  Serial.print("R = ");
  Serial.print(redFrequency);
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  Serial.print(" B = ");
  Serial.println(blueFrequency);

  // Check if the detected color matches the conditions for detecting money
  if (redFrequency >= 65 && redFrequency <= 75 &&
      greenFrequency >= 255 && greenFrequency <= 275 &&
      blueFrequency >= 185 && blueFrequency <= 205) {
    Serial.println("Uang 100000 terdeteksi!");
  }

  // Check if the detected color matches the conditions for detecting money
  if (redFrequency >= 95 && redFrequency <= 115 &&
      greenFrequency >= 60 && greenFrequency <= 75 &&
      blueFrequency >= 50 && blueFrequency <= 60) {
    Serial.println("Uang 50000 terdeteksi!");
  }

  // Check if the detected color matches the conditions for detecting money
  if (redFrequency >= 170 && redFrequency <= 190 &&
      greenFrequency >= 60 && greenFrequency <= 80 &&
      blueFrequency >= 100 && blueFrequency <= 120) {
    Serial.println("Uang 20000 terdeteksi!");
  }

  // Check if the detected color matches the conditions for detecting money
  if (redFrequency >= 70 && redFrequency <= 90 &&
      greenFrequency >= 170 && greenFrequency <= 195 &&
      blueFrequency >= 80 && blueFrequency <= 95) {
    Serial.println("Uang 10000 terdeteksi!");
  }

  // Check if the detected color matches the conditions for detecting money
  if (redFrequency >= 40 && redFrequency <= 60 &&
      greenFrequency >= 50 && greenFrequency <= 70 &&
      blueFrequency >= 70 && blueFrequency <= 95) {
    Serial.println("Uang 5000 terdeteksi!");
  }

  // Check if the detected color matches the conditions for detecting money
  if (redFrequency >= 75 && redFrequency <= 90 &&
      greenFrequency >= 80 && greenFrequency <= 90 &&
      blueFrequency >= 65 && blueFrequency <= 75) {
    Serial.println("Uang 2000 terdeteksi!");
  }

  delay(1000);
}
