/*
Coded by Marjan Olesch
Sketch from Insctructables.com
Open source - do what you want with this code!
*/
#include <Servo.h>


int value = 0; // set values you need to zero

Servo firstESC; //Create as much as Servoobject you want. You can controll 2 or more Servos at the same time

void setup() {
  //pinMode(6, OUTPUT);
  firstESC.attach(6);    // attached to pin 9 I just do this with 1 Servo
  Serial.begin(115200);    // start serial at 9600 baud
}

void loop() {

//First connect your ESC WITHOUT Arming. Then Open Serial and follo Instructions
 
  //analogWrite(6, value);
  firstESC.writeMicroseconds(value);
 
  if(Serial.available()) {
    value = Serial.parseInt();    // Parse an Integer from Serial
    Serial.println(value);
  }
}
