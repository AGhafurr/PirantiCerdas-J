#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#define SENSORPIN 34
#define LEDPIN 25

const char* ssid = "Ghaf";
const char* password = "ghaffffff";
const char* serverName = "http://localhost/piranti/index.php";

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
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
  int ldr_value = analogRead(SENSORPIN);
  if(ldr_value > 100) {
      Serial.println(" Cahaya Terang ");
      digitalWrite(LEDPIN, LOW);
      Serial.print("Intensitas Cahaya: ");
      Serial.print(ldr_value);
      Serial.println();
    }
    else {
      Serial.println("Cahaya Gelap ");
      digitalWrite(LEDPIN, HIGH);
      Serial.print("Intensitas Cahaya: ");
      Serial.print(ldr_value);
      Serial.println();
    }
    delay(100);
  String url = serverName;
  url += "?ldr_value=";
  url += String(ldr_value);

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
  delay(1000);
}