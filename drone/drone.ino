#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#include "err.h"      // User-level error reporting code
#include "altitude.h" // Altitude monitoring code
#include "lights.h"   // Lighting up the skies
#include "sound.h"    // Microphone / audio reading code
#include "motor.h"    // Motor control
#include "pid.h"      // Flight control

/* Remove this to build the final program with fewer lines of code. */
#define DEBUG

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
  
  // Initialize motors, esc, etc
  
  // Initialize microphone, EQ module, etc
  setupSound();
  
  // Initialize lights
  setupLights();
  
  // Initialize drone state
  DRONE_STATE = STATE_FLYING;
  
  // Give the barometer time to start up (approx. 1 second)
  delay(5000);
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
      float altitude = readAltitude();
      
      bool beatDidOccur = readSound();

      updateLightsWithBeatDidOccur(beatDidOccur);
      
      // do something with the altitude.
      break;
  }
  
  if (getError()) {
     /* handle errors */
     if (DRONE_ERROR & ERROR_TYPE_BAROMETER) {
        // TODO: Assign this to a specific piece of failing equipment
     }
  }
}


