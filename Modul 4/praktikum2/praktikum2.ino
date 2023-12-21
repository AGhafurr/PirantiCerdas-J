#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <MPU6050_tockn.h>// Anda harus mengganti ini dengan library yang sesuai untuk sensor MPU6050


const char* ssid = "Ghaf";
const char* password = "ghaffffff";
const char* serverName = "http://192.168.28.246/Prakt6/index.php"; // Sesuaikan dengan alamat server Anda

MPU6050 mpu6050(Wire);

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
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
  Serial.println("Connected to " + wifiName);
  Serial.println("Local IP WIFI: " + localwifiIP);
}

void loop() {
  mpu6050.update();
  Serial.print("anglex : "); 
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangley : ");
  Serial.print(mpu6050.getAngleY()); 
  Serial.print("\tanglez : ");
  Serial.println(mpu6050.getAngleZ());

  // Cek sudut miring 
  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();
  float angleZ = mpu6050.getAngleZ();

  String kemiringan;

  if (angleX > 10) {
    // Sudut miring ke depan
    kemiringan = "depan";
    Serial.println("Sudut miring depan");
  } else if (angleX < -10) {
    // Sudut miring ke belakang
    kemiringan = "belakang";
    Serial.println("Sudut miring belakang");
  } else if (angleY > 10) {
    // Sudut miring ke kanan
    kemiringan = "kanan";
    Serial.println("Sudut miring kanan");
  } else {
    // Sudut miring ke kiri
    kemiringan = "kiri";
    Serial.println("Sudut miring kiri");
  }

  String angka_sumbu = String(angleX) + "," + String(angleY);

  // Kirim data ke server PHP
  String url = serverName;
  url += "?angka_sumbu=";
  url += angka_sumbu; 
  url += "&kemiringan=";
  url += kemiringan;

  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.POST("");
  if (httpResponseCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  delay(5000); // Delay sebelum mengirim data kembali
}
