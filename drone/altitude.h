
#ifndef ALTITUDE_H
#define ALTITUDE_H

/* Returns the current altitude in meters as a float. */
float readAltitude();

/* The barometer object. */
Adafruit_BMP085_Unified __barometer = Adafruit_BMP085_Unified(10085);

/* Sea level pressure in RI -- used to calculate alt */
const float SEA_LEVEL_PRESSURE_RI = 1027.6;

#endif
