#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#include "err.h" // User-level error reporting code
#include "altitude.h" // Altitude monitoring code



/* Remove this to build the final program with fewer lines of code. */
#define DEBUG

/* Sea level pressure in RI -- used to calculate alt */
const float SEA_LEVEL_PRESSURE_RI = 1027.6;

/* The global drone state. oooo */
short DRONE_STATE = 0;
const short STATE_ERROR = -1;
const short STATE_INITIALIZING = 0;
const short STATE_READY = 1;
const short STATE_FLYING = 2;

void setup(void) {
  Serial.begin(9600);
  
  clearError();
  
  /* Barometer init code */
  Serial.println("Initializing pressure sensor.");
  if (!__barometer.begin()) {
      Serial.println("Barometer could not be initialized."); 
      setError(ERROR_TYPE_BAROMETER);
  }
  
  /* TODO: */
  
  // Initialize motors, esc, etc.
  
  // Initialize microphone, EQ module, etc.
  
  // Initialize LED lights.
  
  // Give the barometer time to start up.
  DRONE_STATE = STATE_INITIALIZING;
  
  delay(1000);
}



void loop() {
  
  switch (DRONE_STATE) {
    case STATE_INITIALIZING:
      // TODO: arm ESC -> transition to STATE_READY
      break;
    case STATE_READY:
      // TODO: Initialize Flight control, get off the ground, etc.
      
      // Useful functions: 
      //     float getCurrentAltitude();
      break;
    case STATE_FLYING:
      // TODO: Flight control.
      break;
  }
  
  if (getError()) {
     /* handle errors */
     if (DRONE_ERROR & ERROR_TYPE_BAROMETER) {
        // TODO: Assign this to a specific piece of failing equipment
     }
  }
}


