#include "bluetooth.h"

#define LAND 49
#define UP_THRESHOLD 50
#define DOWN_THRESHOLD 51

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

void readBLE() {
  // If there's any input...
  if(ble_available()) {
    // Read input.
    int c = ble_read();

    if (c == LAND) {
      
    } else if (c == UP_THRESHOLD) {
      
    } else if (c == DOWN_THRESHOLD) {
      
    }
  }
  
  // Process BLE events.
  ble_do_events();
}

