#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define S0 D3
#define S1 D4
#define S2 D5
#define S3 D6
#define sensorOut D7

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid = "Charity_Server";
const char *password = "gemanurani12";

int uang = 0;        // Money
bool status = false; // Status

void setup()
{
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  WiFi.begin(ssid, password);
  Wire.begin(4, 5);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  while (WiFi.status() != WL_CONNECTED)
  {
    lcd.setCursor(0, 0);
    lcd.print(" Menghubungkan");
    lcd.setCursor(0, 1);
    lcd.print("Ke Internet ....");
    Serial.println("Menghubungkan Ke Wifi ...");
    digitalWrite(D0, HIGH);
    digitalWrite(D8, LOW);
    delay(1000);
  }
  lcd.clear();
  digitalWrite(D8, HIGH);
  digitalWrite(D0, LOW);
  Serial.println("Terhubung Ke Wifi !");
  lcd.setCursor(0, 0);
  lcd.print("    Berhasil    ");
  lcd.setCursor(0, 1);
  lcd.print(" Terhubung >_< ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Simulasi     ");
  lcd.setCursor(0, 1);
  lcd.print("  Charity  Box  ");
}

void resetLog()
{
  for (int i = 0; i < 8; i++)
  {
    Serial.println();
  }
}

void proses()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(D0, HIGH);
    digitalWrite(D8, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Syukron     ");
    lcd.setCursor(0, 1);
    lcd.print("Rp.");
    lcd.setCursor(4, 1);
    lcd.print(String(uang));

    WiFiClientSecure client;

    const char *host = "script.google.com";
    const int httpsPort = 443;

    String url = "/macros/s/AKfycbwIDv-xaH1mlq1XinHhlVLbiWaZ3WtWIgdIWLd0qxWVzUYvR-wssykmXi1-Q9dRUlK3/exec";
    url += "?value=" + String(uang) + "&status=" + (status ? "true" : "false");

    Serial.println("Menghubungkan Ke Server Database ...");
    Serial.println(host);

    client.setInsecure();

    if (!client.connect(host, httpsPort))
    {
      Serial.println("Gagal Terhubung Dengan Server, Silahkan Coba Lagi");
      return;
    }

    Serial.println("Berhasil Terhubung Ke Server Database");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: ESP8266\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("Permintaan Terkirim, Menunggu Server Merespon [ Jika Ada ]");

    delay(2500);

    if (client.available())
    {
      // String line = client.readStringUntil('\r');
      // Serial.print(line);
      Serial.println("Server Database Berhasil Merespon, Melanjutkan Proses Berikutnya ...");
      digitalWrite(D8, HIGH);
      digitalWrite(D0, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Berhasil     ");
      lcd.setCursor(0, 1);
      lcd.print("Kirim Ke Server !");
    }

    Serial.println("Menutup Koneksi Setelah Berhasil Terhubung Ke Server Database ...");
    client.stop();
    delay(1000);
    resetLog();
    uang = 0;
    status = false;
    digitalWrite(D8, HIGH);
    digitalWrite(D0, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Simulasi     ");
    lcd.setCursor(0, 1);
    lcd.print("  Charity  Box  ");
  }
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Menghubungkan");
    lcd.setCursor(0, 1);
    lcd.print("Ke Internet ....");
    Serial.println("Menghubungkan Ke Wifi ...");
    digitalWrite(D0, HIGH);
    digitalWrite(D8, LOW);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 5)
    {
      WiFi.begin(ssid, password);
      delay(5000); // Delay tambahan setelah memulai koneksi WiFi
      attempts++;
    }

    // Jika berhasil terhubung, tampilkan pesan dan lanjutkan
    if (WiFi.status() == WL_CONNECTED)
    {
      lcd.clear();
      digitalWrite(D8, HIGH);
      digitalWrite(D0, LOW);
      Serial.println("Terhubung Ke Wifi !");
      lcd.setCursor(0, 0);
      lcd.print("    Berhasil    ");
      lcd.setCursor(0, 1);
      lcd.print(" Terhubung >_< ");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Simulasi     ");
      lcd.setCursor(0, 1);
      lcd.print("  Charity  Box  ");
    }
  }
  else
  {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    int redFrequency = pulseIn(sensorOut, LOW);

    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    int greenFrequency = pulseIn(sensorOut, LOW);

    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    int blueFrequency = pulseIn(sensorOut, LOW);

    // Serial.print("R = ");
    // Serial.print(redFrequency);
    // Serial.print(" G = ");
    // Serial.print(greenFrequency);
    // Serial.print(" B = ");
    // Serial.println(blueFrequency);

    if (digitalRead(D0) == LOW)
    {
      if (redFrequency >= 75 && redFrequency <= 90 &&
          greenFrequency >= 80 && greenFrequency <= 90 &&
          blueFrequency >= 65 && blueFrequency <= 75)
      {
        Serial.println("Uang 2000 terdeteksi");
        uang = 2000;
        status = true;
        proses();
      }
      else if (redFrequency >= 40 && redFrequency <= 60 &&
               greenFrequency >= 50 && greenFrequency <= 70 &&
               blueFrequency >= 70 && blueFrequency <= 95)
      {
        Serial.println("Uang 5000 terdeteksi");
        uang = 5000;
        status = true;
        proses();
      }
      else if (redFrequency >= 70 && redFrequency <= 90 &&
               greenFrequency >= 170 && greenFrequency <= 195 &&
               blueFrequency >= 80 && blueFrequency <= 95)
      {
        Serial.println("Uang 10000 terdeteksi");
        uang = 10000;
        status = true;
        proses();
      }
      else if (redFrequency >= 170 && redFrequency <= 190 &&
               greenFrequency >= 60 && greenFrequency <= 80 &&
               blueFrequency >= 100 && blueFrequency <= 120)
      {
        Serial.println("Uang 20000 terdeteksi");
        uang = 20000;
        status = true;
        proses();
      }
      else if (redFrequency >= 95 && redFrequency <= 115 &&
               greenFrequency >= 60 && greenFrequency <= 75 &&
               blueFrequency >= 50 && blueFrequency <= 60)
      {
        Serial.println("Uang 50000 terdeteksi");
        uang = 50000;
        status = true;
        proses();
      }
      else if (redFrequency >= 65 && redFrequency <= 75 &&
               greenFrequency >= 255 && greenFrequency <= 275 &&
               blueFrequency >= 185 && blueFrequency <= 205)
      {
        Serial.println("Uang 100000 terdeteksi");
        uang = 100000;
        status = true;
        proses();
      }
    }
  }
  delay(250);
}
