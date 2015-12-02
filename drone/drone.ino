#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

/* Remove this to build the final program with fewer lines of code. */
#define DEBUG

Adafruit_BMP085_Unified __barometer = Adafruit_BMP085_Unified(10085);

/* Sea level pressure in RI -- used to calculate alt */
const float SEA_LEVEL_PRESSURE_RI = 1027.6;

/* General state flags -- flick on one bit of these if your stuff is fucked up */
unsigned long DRONE_ERROR = 0;

/* Sets an error bit in the global error long. */
void setError(int pos) {
  #ifdef DEBUG
  if (pos > sizeof(long)) {
    Serial.println("ERROR -- setError() failed.");
    Serial.print("Warning -- bit out of range in error: ");
    Serial.print(pos);
    Serial.print(" -- width of long is: ");
    Serial.println(sizeof(long));
    while(1);
  }
  if (pos < 0) {
    Serial.println("Warning -- tried to set error bit at negative index.");
  }
  #endif
  
  /* Set the bit in the error number. */
  DRONE_ERROR = DRONE_ERROR & (1 << pos);
}

/* Returns true (non-zero) if there is an error, o.w false. */
inline int getError() {
  return DRONE_ERROR;
}

/* Clears the value of the error variable. */
inline void clearError() {
  DRONE_ERROR = 0;
}








void setup(void) {
  Serial.begin(9600);
  
  clearError();
  
  /* Barometer init code */
  Serial.println("Initializing pressure sensor.");
  if (!__barometer.begin()) {
      Serial.println("Barometer could not be initialized."); 
  }
  
  /* TODO: */
  
  // Initialize motors, esc, etc.
  
  // Initialize microphone, EQ module, etc.
  
  // Initialize LED lights.
  
  // Give the barometer time to start up.
  DRONE_STATE = STATE_INITIALIZING;
  
  delay(1000);
}

short DRONE_STATE = 0;

const short STATE_INITIALIZING = 0;


void loop() {
  
  switch (DRONE_STATE) {
    case STATE_INITIALIZING:
      // TODO: arm ESC so that we can fly outchea
      break;
    case STATE_RUNNING:
      // TODO: Flight control, read microphone input, etc.
      break;
    case STATE_ERROR:
      // TODO: land, if possible.
      break;
  }

}







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
    
  }
  
  return __last_altitude;
}
