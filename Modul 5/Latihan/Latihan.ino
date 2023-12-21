#define BLYNK_TEMPLATE_ID "TMPL6phks4wZR"
#define BLYNK_TEMPLATE_NAME "Modul5"
#define BLYNK_AUTH_TOKEN "12uevl9kYzOPzASSKbdSyoHmnFNOcfNF"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define LIGHT_SENSOR_PIN 32

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Ghaf";
char pass[] =  "ghaffffff";

void send_data(){
  delay(1000);
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("Analog Value = ");
  Serial.print(analogValue);

  Blynk.virtualWrite(V0, analogValue);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, send_data);

}

void loop() {
  Blynk.run();
  timer.run();
}
