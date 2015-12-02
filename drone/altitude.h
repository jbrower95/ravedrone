
#ifndef ALTITUDE_H
#define ALTITUDE_H

/* Returns the current altitude in meters as a float. */
float getCurrentAltitude();

/* The barometer object. */
Adafruit_BMP085_Unified __barometer = Adafruit_BMP085_Unified(10085);

#endif
