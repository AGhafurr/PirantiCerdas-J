// keg 1 > kesambung ke open accces 
#include <WiFi.h>

const char* ssid = "Galaxy m53";
const char* password = "12345678";
const char* openSsid = "Ghaf"; 

void setup() {
  Serial.begin(9600);
  Serial.printf("Mencoba terhubung ke %s...\n", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");

    //kesambung ke open acces klo gabisa konek
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Gagal terhubung ke WiFi. Mencoba WiFi Open Access...");
      WiFi.begin(openSsid);
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
    Serial.print("Nama SSID: ");
    Serial.println(WiFi.SSID());
  }
}

void loop() {
  // Loop utama program Anda
}