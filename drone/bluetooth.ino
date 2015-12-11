#ifdef BLUETOOTH

#include "bluetooth.h"
#include <SPI.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <RBL_services.h>

void setupBLE() {
  // Allow communication with Serial Peripheral Interface device
  // Set up communication details: clock polarity/phase, bit order, etc.
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();

  // Initialize BLE library.
  ble_begin();

  // Set a custom BLE name.
  ble_set_name("RaveDrone");
}

// Gets the current threshold used for detecting beats 
// and writes the digits, one by one, to the attached device 
// for the user to view
void writeCurrentThreshold(int threshold) {
  int t = threshold;
  int digits[sizeof(String(t))-1];
  Serial.println(sizeof(String(t)));
  int i = 0;
  if (t == 0) {
    digits[0] = 48;
  }
  while (t > 0) {
    digits[i] = (t % 10) + 48;
    t = t / 10;
    i++;
  }
  for (int i = sizeof(String(t)) - 2; i >= 0; i--) {
    ble_write(digits[i]);
  }
  ble_do_events();
}

// Reads for input from the attached device.
// The input is parsed in the main loop.
int readBLE() {
  // If there's any input...
  if(ble_available()) {
    // Read input.
    int c = ble_read();
    return c;
  }
  
  // Process BLE events.
  ble_do_events();
  return -1;
}

#endif
