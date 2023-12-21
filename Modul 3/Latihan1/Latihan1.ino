#include <Wire.h>
#include <WiFi.h>
#include <MPU6050_tockn.h>

const char* ssid = "No"; // Ganti dengan nama WiFi Anda
const char* password = "11111111"; // Ganti dengan kata sandi WiFi Anda

MPU6050 mpu6050(Wire);

int threshold = 10; // Ambang batas perubahan sudut
int currentAngle = 0;
int previousAngle = 0;
bool connected = false;

int buzzerPin = 18; // Ganti dengan pin output buzzer yang Anda gunakan

void setup() {
  Wire.begin();
  Serial.begin(19200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  connected = true;
  mpu6050.begin();
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (connected) {
    mpu6050.update();
    float angelX = mpu6050.getAngleX();
    float angelY = mpu6050.getAngleY();

    if (abs(angelX) > threshold) {
      if (angelX > 0) {
        // Logika untuk peringatan sudut kanan
        Serial.println("Peringatan: Sudut ke kanan terlampaui");
        tone(buzzerPin, 1000); // Frekuensi bunyi buzzer untuk peringatan sudut kanan
        delay(100); // Durasi bunyi buzzer (singkatkan delay)
        noTone(buzzerPin); // Matikan bunyi buzzer
      } else {
        // Logika untuk peringatan sudut kiri
        Serial.println("Peringatan: Sudut ke kiri terlampaui");
        tone(buzzerPin, 8000); // Frekuensi bunyi buzzer untuk peringatan sudut kiri
        delay(100); // Durasi bunyi buzzer (singkatkan delay)
        noTone(buzzerPin); // Matikan bunyi buzzer
      }
    }

    if (abs(angelY) > threshold) {
      if (angelY > 0) {
        // Logika untuk peringatan gerakan ke depan
        Serial.println("Peringatan: Gerakan ke depan terlampaui");
        tone(buzzerPin, 3000); // Frekuensi bunyi buzzer untuk gerakan ke depan
        delay(100); // Durasi bunyi buzzer (singkatkan delay)
        noTone(buzzerPin); // Matikan bunyi buzzer
      } else {
        // Logika untuk peringatan gerakan ke belakang
        Serial.println("Peringatan: Gerakan ke belakang terlampaui");
        tone(buzzerPin, 6000); // Frekuensi bunyi buzzer untuk gerakan ke belakang
        delay(100); // Durasi bunyi buzzer (singkatkan delay)
        noTone(buzzerPin); // Matikan bunyi buzzer
      }
    }
  }
}