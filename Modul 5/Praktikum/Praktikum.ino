#define BLYNK_TEMPLATE_ID "TMPL6phks4wZR"
#define BLYNK_TEMPLATE_NAME "Modul5"
#define BLYNK_AUTH_TOKEN "12uevl9kYzOPzASSKbdSyoHmnFNOcfNF"
#include <Wire.h>

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define SENSORPIN 32
#define RELAY_PIN 16

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Ghaf";
char pass[] = "ghaffffff";

void updateLightStatus() {
  delay(5000);
  int lightValue = analogRead(SENSORPIN);

  if (lightValue < 500) {
    digitalWrite(RELAY_PIN, LOW);  
    Blynk.virtualWrite(V1, "Gelap");
    Serial.print("Indikator = Gelap ");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V1, "Terang");
    Serial.print("Indikator = Terang ");
  }

  Serial.print("Analog Value = ");
  Serial.println(lightValue);
  Blynk.virtualWrite(V0, lightValue);
}

BLYNK_WRITE(V2) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite(RELAY_PIN, LOW);
  } else {
    digitalWrite(RELAY_PIN, HIGH);
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(SENSORPIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  timer.setInterval(1000L, updateLightStatus);
}

void loop() {
  Blynk.run();
  timer.run();
}
