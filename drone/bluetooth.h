#ifndef BLUETOOTH_H
#define BLUETOOTH_H

// Enumerated input from attacked BLE device.
#define LAND 0
#define UP_THRESHOLD 1
#define DOWN_THRESHOLD 2

// Call this before adding any other BLE functions.
void setupBLE();

// Call this to read in from bluetooth.
int readBLE();

#endif
