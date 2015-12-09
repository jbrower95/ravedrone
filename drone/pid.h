#ifndef PID_H
#define PID_H

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



#endif
