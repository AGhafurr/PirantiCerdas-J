#define LIGHT_SENSOR_PIN 32

int redPin = 2;
int greenPin = 4;
int bluePin = 16;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  if(analogValue < 500 ){
     setColor(0, 0, 0); //red
     Serial.print("Analog Value = ");
     Serial.print(analogValue);
     Serial.println("");
  }
  else if(analogValue < 1000 && analogValue > 500){
    setColor(100, 0, 0); //green
    Serial.print("Analog Value = ");
    Serial.print(analogValue);
    Serial.println("");
  }
  else{
    setColor(255, 0, 0); //blue
    Serial.print("Analog Value = ");
    Serial.print(analogValue);
    Serial.println("");
  }
  
}

void setColor(int red, int green, int blue){
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}