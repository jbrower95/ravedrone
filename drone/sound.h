#ifndef SND_H
#define SND_H

// Call this before calling any other sound functions.
void setupSound();

// Call this to read fresh values for the EQ.
bool readSound();

// Access this array to read the values for the EQ.
float __SOUND[7];

int increaseOrigThreshold();
int decreaseOrigThreshold();

#endif
