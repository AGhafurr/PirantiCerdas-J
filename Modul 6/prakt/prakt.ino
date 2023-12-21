#include <Wire.h>
#include <MPU6050_tockn.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const char* ssid = "Ghaf";
const char* password = "ghaffffff";
const char* serverName = "http://192.168.236.192/prakt6/index.php";

MPU6050 mpu6050(Wire);

const int ledPin = 18;
const int buzzerPin = 33; // Pin buzzer terhubung ke pin 33 pada ESP32


void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  delay(1000);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Connecting to WiFi...");
  }

  String wifiName = WiFi.SSID();
  String localwifiIP = WiFi.localIP().toString();
  Serial.println();
  Serial.println("Connected to wifiName");
  Serial.println("Local IP WIFI: " + localwifiIP);
}

void loop() {
  mpu6050.update();
  
  // Cek sudut miring 
  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();
  // float angleZ = mpu6050.getAngleZ();

  String kemiringan;
  String buzzer;
  String led;

  if (isFlat && (abs(angleX) > 10 || abs(angleY) > 10)) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, LOW);
    kemiringan = "Bidang_tidak_datar";
    buzzer = "Buzzer_Hidup";
    led = "LED_Mati";
    Serial.println(angleX);
    Serial.println(angleY);
    Serial.println(kemiringan);
    Serial.println(buzzer);
    Serial.println(led);
  } else if (!isFlat && abs(angleX) <= 10 && abs(angleY) <= 10) {
    // MPU kembali datar, buzzer dimatikan
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    kemiringan = "Bidang_datar";
    buzzer = "Buzzer_Mati";
    led = "LED_Hidup";
    Serial.println(angleX);
    Serial.println(angleY);
    Serial.println(kemiringan);
    Serial.println(buzzer);
    Serial.println(led);
  }

  // Kirim data ke server PHP
  String url = serverName;
  url += "?angka_sumbuX=";
  url += String(angleX); 
  url += "&angka_sumbuY=";
  url += String(angleY);
  url += "&kemiringan=";
  url += kemiringan;
  url += "&indikator_buzzer=";
  url += buzzer;
  url += "&indikator_led=";
  url += led;

  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.POST("");
  if (httpResponseCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.GET();
  http.end();
  delay(5000); 
}