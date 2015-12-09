#ifdef BLUETOOTH

#include "bluetooth.h"
#include <SPI.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <RBL_services.h>

void setupBLE() {
  // TODO: Get rid of this todo. Possibly makes using pin 7 or 8 really shitty?
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();

  // Initialize BLE library.
  ble_begin();

  // Set a custom BLE name.
  ble_set_name("RaveDrone");
}

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
    Serial.print("digit: ");
    Serial.println(digits[i]);
    ble_write(digits[i]);
  }
  ble_do_events();
}

int readBLE() {
  // If there's any input...
  if(ble_available()) {
    // Read input.
    int c = ble_read();
    return c;
  }
  
  // Process BLE events.
  ble_do_events();
}

#endif
