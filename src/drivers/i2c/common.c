#include "common.h"

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

inline bool reserved_addr(uint8_t addr) { return (addr & 0x78) == 0 || (addr & 0x78) == 0x78; }

pico_error_t i2c_scan(void) {
  pico_error_t ret = PICO_ERROR_GENERIC;

#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
  printf("\r\nI2C Bus Scan\r\n");
  printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");
#endif  // LOG_LEVEL_VERBOSE

  for (int addr = 0; addr < (1 << 7); ++addr) {
#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
    if (addr % 16 == 0) {
      printf("%02x ", addr);
    }
#endif  // LOG_LEVEL_VERBOSE

    // Perform a 1-byte dummy read from the probe address. If a slave
    // acknowledges this address, the function returns the number of bytes
    // transferred. If the address byte is ignored, the function returns -1.

    // Skip over any reserved addresses.
    uint8_t rxdata;
    if (!reserved_addr(addr)) {
      ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);
    }
#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
    printf(ret < 0 ? "." : "@");
    printf(addr % 16 == 15 ? "\r\n" : "  ");
#endif  // LOG_LEVEL_VERBOSE
  }

#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
  printf("Done.\r\n");
#endif  // LOG_LEVEL_VERBOSE

  return ret;
}
