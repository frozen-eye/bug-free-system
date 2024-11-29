#include "common.h"

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

inline bool reserved_addr(uint8_t addr) { return (addr & 0x78) == 0 || (addr & 0x78) == 0x78; }

pico_error_t i2c_probe(uint8_t addr) {
  // Perform a 1-byte dummy read from the probe address. If a slave
  // acknowledges this address, the function returns the number of bytes
  // transferred. If the address byte is ignored, the function returns -1.

  // Skip over any reserved addresses.
  uint8_t rxdata = 0xff;
  pico_error_t ret = PICO_ERROR_GENERIC;
  if (!reserved_addr(addr)) {
    ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);
  }

  return ret >= PICO_ERROR_NONE ? PICO_ERROR_NONE : ret;
}
