#include "sound.h"

int readPin = 0; // Read from analog pin 0
int strobePin = 2; // STROBE  on digital pin 2
int resetPin = 3; // RESET on digital pin 3

// The average of the current sound input, and the previous loops average
float avg = 0;
float prevAvg = 0;

// Set up the threshold and the decay rate, for use when detecting a beat
float origT = 50;
static float thresholdMin = origT - 40;
static float threshold = origT;
static float decayRate = .9;

// With no input, MSGEQ7 outputs around 50-80 in each spectrum.
// Use this to filter the values.
static int filter = 80;
  
void setupSound() {
    pinMode(readPin, INPUT);
    pinMode(strobePin, OUTPUT);
    pinMode(resetPin, OUTPUT);
    analogReference(DEFAULT);
    
    digitalWrite(resetPin, LOW);
    digitalWrite(strobePin, HIGH);
    
    Serial.println("Sound initialized");
}

int increaseOrigThreshold() {
  origT += 50;
  return origT;
}

int decreaseOrigThreshold() {
  origT -= 50;
  return origT;
}

bool readSound() {
    // Reset to allow strobe to work
    digitalWrite(resetPin, HIGH);
    digitalWrite(resetPin, LOW);
    prevAvg = avg;

    avg = 0;
    
    // MSGEQ7 gathers 7 spectrum values (63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz and 16kHz)
    for (int i = 0; i < 7; i++)
    {
      digitalWrite(strobePin, LOW);
      delayMicroseconds(30); // Need to allow output to settle (doesn't work right without this)
      
      // Read in the ith spectrum value
      __SOUND[i] = analogRead(readPin);
      
      // Value should only be in the range from filter to 1023
      __SOUND[i] = constrain(__SOUND[i], filter, 1023);
      
      // With values now only between filter and 1023, remap relatively within range 0-255
      __SOUND[i] = map(__SOUND[i], filter, 1023, 0, 255);

      // Average in the spectrum value. 1/7 = .142857...
      avg += __SOUND[i] * (.142857142857);
      digitalWrite(strobePin, HIGH);
    }

    // Make sure threshold only decays until it reaches the minimum value
    if (threshold > thresholdMin) {
      threshold *= decayRate;
    }

    // If the new average has changed more than the threshold, we found a beat!
    if (abs(avg - prevAvg) >= threshold) {
      threshold = origT;
      return true;
    } else {
      return false;
    }
}

