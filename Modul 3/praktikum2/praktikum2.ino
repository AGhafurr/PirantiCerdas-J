#include <MPU6050_tockn.h>
#include <Wire.h>
#include <WiFi.h>

const char* ssid = "Kost BU PUR"; // Ganti dengan SSID WiFi Anda
const char* password = "tvkabel1buk"; // Ganti dengan kata sandi WiFi Anda

MPU6050 mpu6050(Wire);
int buzzerPin = 13; // Pin buzzer

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
  pinMode(buzzerPin, OUTPUT);

  // Koneksi WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan ke WiFi...");
  }
  Serial.println("Terhubung ke WiFi!");
}

void loop() {
  mpu6050.update();
  Serial.print("angleX: ");
  Serial.print(mpu6050.getAngleX());
  Serial.print(" angleY: ");
  Serial.print(mpu6050.getAngleY());
  Serial.print(" angleZ: ");
  Serial.print(mpu6050.getAngleZ());
  Serial.println();

  // Cek sudut miring dan mengendalikan buzzer sesuai kondisi
  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();
  float angleZ = mpu6050.getAngleZ();


  if (angleX > 10) {
    // Sudut miring ke depan
    tone(buzzerPin, 3000); // Bunyi dengan frekuensi 3000 Hz
    Serial.println("Sudut miring depan");
  } else if (angleX < -10) {
    // Sudut miring ke belakang
    tone(buzzerPin, 2000); // Bunyi dengan frekuensi 2000 Hz
    Serial.println("Sudut miring belakang");
  } else if (angleY > 10) {
    // Sudut miring ke kanan
    tone(buzzerPin, 1500); // Bunyi dengan frekuensi 1500 Hz
    Serial.println("Sudut miring kanan");
  } else if (angleY < -10) {
    // Sudut miring ke kiri
    tone(buzzerPin, 1000); // Bunyi dengan frekuensi 1000 Hz
    Serial.println("Sudut miring kiri");
  } else {
    noTone(buzzerPin); // Matikan buzzer jika tidak ada perubahan sudut signifikan
  }

  delay(500); // Interval pembacaan sensor
}