#include "motor.h"

// TODO: Control these motors. 
#include <Servo.h>

int value = 0;

Servo firstESC;
motor_t m;

void setup() {
  //pinMode(6, OUTPUT);
  firstESC.attach(6);    // attached to pin 9 I just do this with 1 Servo
  makeMotor(6, m, firstESC);
  Serial.begin(115200);    // start serial at 9600 baud
}

void loop() {
  //analogWrite(6, value);
  m.targetLevel = value;
  tickMotor(m, firstESC);
 
  if(Serial.available()) {
    value = Serial.parseInt();    // Parse an Integer from Serial
    Serial.print("Value: ");
    Serial.println(value);
  }
  
  Serial.print("Current: ");
  Serial.println(m.currentLevel);
  
  delay(100);
}

