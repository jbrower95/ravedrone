#include "sound.h"

int analogPin = 0; // read from multiplexer using analog input 0
int strobePin = 2; // strobe is attached to digital pin 2
int resetPin = 3; // reset is attached to digital pin 3
int spectrumValue[7]; // to hold a2d values

float topAvg = 0;
int range = 150;
float alpha = .5;

void setupSound()
{
 pinMode(analogPin, INPUT);
 pinMode(strobePin, OUTPUT);
 pinMode(resetPin, OUTPUT);
 analogReference(DEFAULT);

 digitalWrite(resetPin, LOW);
 digitalWrite(strobePin, HIGH);

 Serial.println("Sound initialized");
}

void readSound()
{
 digitalWrite(resetPin, HIGH);
 digitalWrite(resetPin, LOW);

 for (int i = 0; i < 7; i++) {
   digitalWrite(strobePin, LOW);
   delayMicroseconds(30); // to allow the output to settle
   __SOUND[i] = analogRead(analogPin);

  if (i == 3) {
    Serial.print(spectrumValue[i]);
    Serial.print("    ");
    if (abs(spectrumValue[i] - topAvg) > range) {
      Serial.println("BEAT");
    }
    topAvg = topAvg * (1 - alpha) + __SOUND[i] * alpha;
  }
  
   digitalWrite(strobePin, HIGH);
 }
}
