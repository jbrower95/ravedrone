#include "lights.h"

const int POWER_PIN = 10;   // the power pin needs PWM
const int RED_PIN = 11;
const int GREEN_PIN = 12; 
const int BLUE_PIN = 13;

const double FADE_RATE = 0.85;

int intensity = 0;
int currentColor = 1;

int colors[][3] = {{LOW, LOW, LOW},     // 0. WHITE
                   {LOW, LOW, HIGH},    // 1. YELLOW
                   {LOW, HIGH, HIGH},   // 2. RED
                   {LOW, HIGH, LOW},    // 3. PURPLE
                   {HIGH, HIGH, LOW},   // 4. BLUE
                   {HIGH, LOW, LOW},    // 5. CYAN
                   {HIGH, LOW, HIGH}};  // 6. GREEN

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
    currentColor++;
    if (currentColor > 6) {
      currentColor = 1;
    }
  } else {
    intensity = max(15, intensity * FADE_RATE);
  }

  // Write updates to lights
  setColorAndIntensity(currentColor, intensity);
}

void setColorAndIntensity(int color, int intensity) {
  analogWrite(POWER_PIN, intensity);
  digitalWrite(RED_PIN, colors[color][0]);
  digitalWrite(GREEN_PIN, colors[color][1]);
  digitalWrite(BLUE_PIN, colors[color][2]);
}

