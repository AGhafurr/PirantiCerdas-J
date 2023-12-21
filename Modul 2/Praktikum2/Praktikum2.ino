#define DO_PIN 32
#define BUZZER 19

void setup() {
  // Put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(DO_PIN, INPUT);
}

void loop() {
  int analogValue = analogRead(DO_PIN);
  if (analogValue < 500) {
    digitalWrite(BUZZER, HIGH); // Buzzer aktif dalam kondisi gelap
    Serial.print("Analog Value = KEADAAN GELAP");
    Serial.println("");
  } else {
    digitalWrite(BUZZER, LOW); // Matikan buzzer dalam kondisi terang
    Serial.print("Analog Value = KEADAAN TERANG");
    Serial.println("");
  }
}
