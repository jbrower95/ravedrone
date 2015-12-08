#include "lights.h"

const int POWER_PIN = 10;   // the power pin needs PWM
const int RED_PIN = 11;
const int GREEN_PIN = 12; 
const int BLUE_PIN = 13;

int intensity = 0;
int r = HIGH;

void setupLights() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Initialize lights to off
  analogWrite(POWER_PIN, 0);
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
}

void updateLightsWithBeatDidOccur(bool beatDidOccur) {
  if (beatDidOccur) {
    intensity = 255;
    r = LOW;
  } else {
    intensity = max(7, intensity * 0.75);
    r = LOW;
  }

  // Write updates to lights
  analogWrite(POWER_PIN, intensity);
  digitalWrite(RED_PIN, r);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

