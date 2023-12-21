#define BLYNK_TEMPLATE_ID "TMPL6phks4wZR"
#define BLYNK_TEMPLATE_NAME "Modul5"
#define BLYNK_AUTH_TOKEN "2p2N2vWy4R1ZRGvoR1tvtBFVfeOpBA0j"

#include <Wire.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BUZZER_PIN 19
DHT dht(26, DHT11);

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Ghaf";
char pass[] = "ghaffffff";

void updateTempratureStatus(){
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Error membaca sensor!");
  } else {
    if (temp > 33) {
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.println(" C ");
      tone(BUZZER_PIN, 10000);
      Blynk.virtualWrite(V1, "Suhu Panas");
      Blynk.virtualWrite(V0, temp);
      Blynk.virtualWrite(V2, 1);
    } else if (temp > 27) {
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.println(" C ");
      tone(BUZZER_PIN, 500);  
      Blynk.virtualWrite(V1, "Suhu Hangat");
      Blynk.virtualWrite(V0, temp);
      Blynk.virtualWrite(V2, 1);
    } else {
      noTone(BUZZER_PIN);
      Blynk.virtualWrite(V1, "Suhu Normal");
      Blynk.virtualWrite(V0, temp);
      Blynk.virtualWrite(V2, 0);
    }
  }
  delay(2000);
}

void setup(){
  dht.begin();
  delay(2000);
  Blynk.begin(auth, ssid, pass);
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  timer.setInterval(1000L, updateTempratureStatus);
}

void loop(){
  Blynk.run();
  timer.run();
}