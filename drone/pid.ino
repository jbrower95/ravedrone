#include "pid.h"
#include "altitude.h"
#include "motor.h"

// Control this large balloon with the power of PID

// Proportionality constant
float kP = 6;
float kI = .7;
float kD = .5;

float Integral = 0;

float lastAltitude = 0;

float target = 0;

void setFlightTarget(int expectedAltitude) {
   target = expectedAltitude; 
}

void flightControl() {
  if (!lastAltitude) {
    lastAltitude = readAltitude();
  }  
  float currentAltitude = readAltitude();
  
  // calculate error
  float error = target - currentAltitude;
  
  if (error > 0) {
    Serial.println("Positive Error! - Engaging motor.");
   setMotorTarget(2000); 
  } else {
    Serial.println("Negative error - disengaging motor.");
   setMotorTarget(1200); 
  }
  
  return;
  
  float P = error * kP;
  float I = Integral * kI;
  float D = (lastAltitude - currentAltitude) * kD;
  
  float Drive = P + I + D;
  
  // If it's too high, it'll clamp to 0 and shut the motor off. 
  Drive = map(constrain(Drive, 0, 100), 0, 100, MIN_LEVEL, MAX_LEVEL);
  
  #ifdef DEBUG
  Serial.print("Target: ");
  Serial.println(target);
  Serial.print("Drive: ");
  Serial.println(Drive);
  #endif
  
  setMotorTarget(Drive);
  
  lastAltitude = currentAltitude;
}
