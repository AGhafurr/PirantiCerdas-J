#include <MPU6050_tockn.h> 
#include <Wire.h>

#define SENSORPIN 34

MPU6050 mpu6050(Wire);

void setup() { 
  Serial.begin(9600); 
  Wire.begin(); 
  mpu6050.begin(); 
  mpu6050.calcGyroOffsets(); 
}

void loop() {
  int ldr_value = analogRead(SENSORPIN);
  if(ldr_value > 0 && ldr_value <50) {
    Serial.println(" keadaan Gelap ");
    Serial.print("Intensitas Cahaya: ");
    Serial.print(ldr_value);
    Serial.println();
  }
  else if(ldr_value > 50 && ldr_value <500) {
    Serial.println(" keadaan Redup ");
    Serial.print("Intensitas Cahaya: ");
    Serial.print(ldr_value);
    Serial.println();
  }
  else if(ldr_value > 500 && ldr_value <2000) {
    Serial.println(" Cahaya Terang ");
    Serial.print("Intensitas Cahaya: ");
    Serial.print(ldr_value);
    Serial.println();
  }
  else {
    Serial.println("Sangat Terang ");
    Serial.print("Intensitas Cahaya: ");
    Serial.print(ldr_value);
    Serial.println();
  }
    
  mpu6050.update();
  Serial.print("anglex : "); 
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangley : ");
  Serial.print(mpu6050.getAngleY()); 
  Serial.print("\tanglez : ");
  Serial.println(mpu6050.getAngleZ());

  // Cek sudut miring 
  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();
  float angleZ = mpu6050.getAngleZ();


  if (angleX > 10) {
    // Sudut miring ke depan
    Serial.println("Sudut miring depan");
  } else if (angleX < -10) {
    // Sudut miring ke belakang
    Serial.println("Sudut miring belakang");
  } else if (angleY > 10) {
    // Sudut miring ke kanan
    Serial.println("Sudut miring kanan");
  } else {
    // Sudut miring ke kiri
    Serial.println("Sudut miring kiri");
  }

  delay(5000);

}