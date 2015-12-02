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
// TO BE USED REAL SOON
 * /* David Wang
 * Code that takes audio input from a 3.5mm cable
 * and flashes an LED strip based on the frequency 
 * of the music.
 *
 * HUGE thanks to the arduino community
 * If you see your code here, I owe you my gratitude
 *
 */

//int analogPin = 0; // MSGEQ7 OUT
//int strobePin = 2; // MSGEQ7 STROBE
//int resetPin = 3; // MSGEQ7 RESET
//int spectrumValue[7];
//
//// MSGEQ7 OUT pin produces values around 50-80
//// when there is no input, so use this value to
//// filter out a lot of the chaff.
//int filterValue = 80;
//
//// LED pins connected to the PWM pins on the Arduino
//
//int ledPinR = 9;
//int ledPinG = 10;
//int ledPinB = 11;
//
//void setup()
//{
//  Serial.begin(9600);
//  // Read from MSGEQ7 OUT
//  pinMode(analogPin, INPUT);
//  // Write to MSGEQ7 STROBE and RESET
//  pinMode(strobePin, OUTPUT);
//  pinMode(resetPin, OUTPUT);
//
//  // Set analogPin's reference voltage
//  analogReference(DEFAULT); // 5V
//
//  // Set startup values for pins
//  digitalWrite(resetPin, LOW);
//  digitalWrite(strobePin, HIGH);
//}
//
//void loop()
//{
//  // Set reset pin low to enable strobe
//  digitalWrite(resetPin, HIGH);
//  digitalWrite(resetPin, LOW);
//
//  // Get all 7 spectrum values from the MSGEQ7
//  for (int i = 0; i < 7; i++)
//  {
//    digitalWrite(strobePin, LOW);
//    delayMicroseconds(30); // Allow output to settle // Probably can't do this
//
//    spectrumValue[i] = analogRead(analogPin);
//
//    // Constrain any value above 1023 or below filterValue
//    spectrumValue[i] = constrain(spectrumValue[i], filterValue, 1023);
//
//    // Remap the value to a number between 0 and 255
//    spectrumValue[i] = map(spectrumValue[i], filterValue, 1023, 0, 255);
//
//    // Remove serial stuff after debugging
//    Serial.print(spectrumValue[i]);
//    Serial.print(" ");
//    digitalWrite(strobePin, HIGH);
//   }
//
//   Serial.println();
//
//   // Write the PWM values to the LEDs
//   // I find that with three LEDs, these three spectrum values work the best
//   analogWrite(ledPinR, spectrumValue[1]); 
//   analogWrite(ledPinG, spectrumValue[4]); 
//   analogWrite(ledPinB, spectrumValue[6]); 
//}

 */
