 #include "altitude.h"
 
 static float __last_altitude = -1;
 static sensors_event_t __event;
 
/**
 *  Task -- Reads an event from the barometer 
 *  and returns current calculated. Returns a cached value
 *  if not available.
 */ 
float getCurrentAltitude() {
  __barometer.getEvent(&__event);
  if (__event.pressure) {
     __last_altitude = __barometer.pressureToAltitude(SEA_LEVEL_PRESSURE_RI, __event.pressure);
  } else {
    setError(ERROR_TYPE_BAROMETER);
  }
  
  return __last_altitude;
}
