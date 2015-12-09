#include "pid.h"
#include "altitude.h"
#include "motor.h"

// Control this fucking balloon
/*
//-------------------- Calculates the PID drive value --------------------
 Actual = analogRead(Position);
 Error = SetPt - Actual;

 if (abs(Error) < IntThresh){ // prevent integral 'windup'
 Integral = Integral + Error; // accumulate the error integral
 }
 else {
 Integral=0; // zero it if out of bounds
 }
 P = Error*kP; // calc proportional term
 I = Integral*kI; // integral term
 D = (Last-Actual)*kD; // derivative term
 Drive = P + I + D; // Total drive = P+I+D
 Drive = Drive*ScaleFactor; // scale Drive to be in the range 0-255
 if (Drive < 0){ // Check which direction to go.
 digitalWrite (Direction,LOW); // change direction as needed
 }
 else { // depending on the sign of Error
 digitalWrite (Direction,HIGH);
 }
 if (abs(Drive)>255) {
 Drive=255;
 }
 analogWrite (Motor,Drive); // send PWM command to motor board
 Last = Actual; // save current value for next time
}
*/

// Proportionality constant
float kP = .7;
float kI = .4;
float kD = .5;

float Integral = 0;

float lastAltitude = 0;

void flightControl(int expectedAltitude) {
  if (!lastAltitude) {
    lastAltitude = getAltitude();
  }  
  float currentAltitude = getAltitude();
  
  // calculate error
  float error = expectedAltitude - currentAltitude;
 
  float P = error * kP;
  float I = Integral * kI;
  float D = (lastAltitude - currentAltitude) * kD;
  
  float Drive = P + I + D;
  Drive = map(constrain(Drive, 0, 50), 0, 50, MIN_LEVEL, MAX_LEVEL);
  
  
  
  
  lastAltitude = currentAltitude;
}
