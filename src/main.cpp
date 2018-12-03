
#include <Arduino.h>
#include "MPU6050.h"

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");

  while(!mpu.begin()) {
    Serial.println("Próba inicjalizacji MPU6050");
    // zapewnia, że watchdog nie zresetuje układu
    yield();
  }
  
  pinMode(BUILTIN_LED, OUTPUT);
}

int counter = 0;
bool state = false;

void loop() {
  float temperature = mpu.readTemperature();
  Vector rawAccel = mpu.readRawAccel();
  Vector rawGyro = mpu.readRawGyro();
  
  Serial.print(String(counter++) + "> GYRO " + String(rawGyro.XAxis) + " " + String(rawGyro.YAxis) + " " + String(rawGyro.ZAxis) );
  Serial.print(" ACCEL: " + String(rawAccel.XAxis) + " " + String(rawAccel.YAxis) + " " + String(rawAccel.ZAxis) );
  Serial.println(" TEMP: " + String(temperature));

  Vector accel = mpu.readNormalizeAccel();
  Vector gyro = mpu.readNormalizeGyro();
  Serial.print("\t GYRO " + String(gyro.XAxis) + " " + String(gyro.YAxis) + " " + String(gyro.ZAxis) );
  Serial.println(" ACCEL: " + String(accel.XAxis) + " " + String(accel.YAxis) + " " + String(accel.ZAxis) );


  state = !state;
  digitalWrite(BUILTIN_LED, state);
  delay(300);
}