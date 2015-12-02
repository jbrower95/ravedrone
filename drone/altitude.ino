 float __last_altitude = -1;
 sensors_event_t __event;
/**
 *  Task -- Reads an event from the barometer 
 *  and returns current calculated. Returns a cached value
 *  if not available.
 */ 
float getCurrentAltitude() {
  bmp.getEvent(&__event);
  if (event.pressure) {
     __last_altitude = bmp.pressureToAltitude(SEA_LEVEL_PRESSURE_RI, event.pressure);
  } else {
    setError(
  }
  
  return __last_altitude;
}
