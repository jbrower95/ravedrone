#ifndef PID_H
#define PID_H

/* Runs a PID loop to maintain the altitude. */
void flightControl(int expectedAltitude);

/* Sets the altitude target for the PID loop. */
void setFlightTarget(int expectedAltitude);

#endif
