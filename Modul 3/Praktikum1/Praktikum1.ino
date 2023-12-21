#include <WiFi.h>

const char* ssid = "Kost BU PUR";
const char* password = "tvkabel1buk";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  
  
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000); 
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  
}

void loop() {
  // put your main code here, to run repeatedly:

}