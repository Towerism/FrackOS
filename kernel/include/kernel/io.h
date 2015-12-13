#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stdint.h>

// Read in a byte from port
static inline uint8_t inb(uint16_t port) {
  uint8_t result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

// Output a byte to port
static inline void outb(uint16_t port, uint8_t data) {
  __asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}

// Read in a word from port
static inline uint16_t inw(uint16_t port) {
  uint16_t result;
  __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

// Output a word to port
static inline void outw(uint16_t port, uint16_t data) {
  __asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}

#endif
