#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>

void kernel_early(void) {
  init_gdt();
  terminal_initialize();
}

void kernel_main(void) {
  printf("%s\n%s\n", "Welcome to FrackOS!", "Still in development...");
  printf("%c", '\b');
}
