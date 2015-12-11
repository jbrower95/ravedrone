#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <EEPROM.h>
#include <Servo.h>

#include "err.h"      // User-level error reporting code
#include "altitude.h" // Altitude monitoring code
#include "lights.h"   // Lighting up the skies
#include "sound.h"    // Microphone / audio reading code
#include "motor.h"    // Motor control
#include "pid.h"      // Flight control
#include "bluetooth.h"// Bluetooth control

/* Remove this to build the final program with fewer lines of code. */
#define DEBUG
//#define BLUETOOTH

/* The global drone state. oooo */
short DRONE_STATE = 0;
const short STATE_ERROR = -1;
const short STATE_INITIALIZING = 0;
const short STATE_READY = 1;
const short STATE_FLYING = 2;
const short STATE_LANDING = 3;

void setup(void) {
  Serial.begin(9600);
  
  clearError();
  
  /* Barometer init code */
  Serial.print("Initializing pressure sensor: ");
  if (!__barometer.begin()) {
      Serial.println("FAILURE."); 
      setError(ERROR_TYPE_BAROMETER);
  }
  Serial.println("OK");
  
  // Initialize motors, sound, lights, BLE.
  setupMotor();
  setupSound();
  setupLights();

  #ifdef BLUETOOTH
  setupBLE();
  #endif
  
  // Initialize drone state
  DRONE_STATE = STATE_INITIALIZING;
  
  // Give the barometer / other parts time to start up.
  delay(5000);
}


int expected_altitude; 

int schedule = 0;

void loop() {
  switch (DRONE_STATE) {
    case STATE_INITIALIZING: {
      // go up 2 meters.
      expected_altitude = readAltitude() + 1;
      setFlightTarget(readAltitude() + 1);
      DRONE_STATE = STATE_FLYING;
      #ifdef DEBUG
      Serial.print("Expected Altitude: ");
      Serial.println(expected_altitude);
      #endif
      break;
    }
    case STATE_LANDING:
      // turn off the motor.
      flightControl();
      tickMotor();
      break;
    case STATE_FLYING:
      const float altitude = readAltitude();
      const bool beat = readSound();

      /* Deal with bluetooth if BLUETOOTH is defined. */
      #ifdef BLUETOOTH
      int c = readBLE(); 
      switch (c) {
        case LAND:
          // to land, set the motor speed to zero.
          DRONE_STATE = STATE_LANDING;
          break;
        case UP_THRESHOLD:
          // If the user turned up the threshold, increase and write
          // new value to device
          writeCurrentThreshold(increaseOrigThreshold());
          break;
        case DOWN_THRESHOLD:
          // If the user turned down the threshold, decrease and write
          // new value to device
          writeCurrentThreshold(decreaseOrigThreshold());
          break;
      }
      #endif
      
      #ifdef DEBUG
      Serial.print("Altitude: ");
      Serial.println(altitude);
      #endif

      bool beatDidOccur = readSound();
      
      updateLightsWithBeatDidOccur(beatDidOccur);
      
      #ifdef DEBUG
      //Serial.print("Beat?: ");
      //Serial.println(beat);
      #endif
      
        // Run once every tick
      flightControl();
      tickMotor();
      
      break;
  }
  
  if (getError()) {
     /* handle errors */
     if (DRONE_ERROR & ERROR_TYPE_BAROMETER) {
        // TODO: Assign this to a specific piece of failing equipment
        Serial.println("Error: Couldn't set up barometer.");
        clearError();
        DRONE_STATE = STATE_LANDING;
     }
  }
  
}


