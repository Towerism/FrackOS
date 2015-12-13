#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_early(void)
{
	terminal_initialize();
}

void kernel_main(void)
{
  printf("%s\n%s\n%s\n",
         "Welcome to FrackOS!",
         "Still in development...",
         "This string is testing backspace functionality..................................");
  printf("%c", '\b');
}
