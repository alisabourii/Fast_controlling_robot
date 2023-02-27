#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>

MPU6050 mpu6050(Wire);

Servo srv;


int left_M = 12;
int left_A = 3;
int left_B = 5;

int right_M = 11;
int right_A = 6;
int right_B = 9;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  srv.attach(13);
  
  pinMode(left_M, OUTPUT);
  pinMode(left_A, OUTPUT);
  pinMode(left_B, OUTPUT);
  pinMode(right_M, OUTPUT);
  pinMode(right_A, OUTPUT);
  pinMode(right_B, OUTPUT);
  pinMode(8, OUTPUT); pinMode(7, OUTPUT);
  
}

long timer = 0;

void loop() {
  mpu6050.update();
  if(millis() - timer > 1000){
    Move();
    Serial.println(mpu6050.getAngleX());
    if(mpu6050.getAngleX() <= -5 && mpu6050.getAngleX() > -10){
      srv.write(45);
      digitalWrite(7,1);
      digitalWrite(8,0);}
    else if(mpu6050.getAngleX() <= -10){
      srv.write(90); 
      digitalWrite(7,1);
      digitalWrite(8,0);}
    else if(mpu6050.getAngleX() >= 5 && mpu6050.getAngleX() < 10){
      srv.write(135);
      digitalWrite(7,0);
      digitalWrite(8,1);}
    else if(mpu6050.getAngleX() >= 10){
      srv.write(180);
      digitalWrite(7,0);
      digitalWrite(8,1);}
   else if(mpu6050.getAngleX() > -5 && mpu6050.getAngleX() < 5){
      srv.write(0);
      digitalWrite(7,0);
      digitalWrite(8,0);}
  }
}

void Move(){
  int pot = map(analogRead(A0), 0,1023, 0,255);
  analogWrite(left_M, pot);
  digitalWrite(left_A,1);
  digitalWrite(left_B,0);

  analogWrite(right_M, pot);
  digitalWrite(right_A,1);
  digitalWrite(right_B,0);

  }
  }
