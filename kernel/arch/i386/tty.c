#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>
#include <kernel/io.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_clear() {
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = make_vgaindex(x, y);
      terminal_buffer[index] = make_vgaentry(' ', terminal_color);
    }
  }
}

void terminal_update_cursor() {
  size_t index = make_vgaindex(terminal_column, terminal_row);
  uint8_t index_high = (index >> 8) & 0xFF;
  uint8_t index_low = index & 0xFF;
  outb(VGA_CTRL, 0x0E);
  outb(VGA_DATA, index_high);
  outb(VGA_CTRL, 0x0F);
  outb(VGA_DATA, index_low);
}

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  terminal_buffer = VGA_MEMORY;

  terminal_clear();
  terminal_update_cursor();
}

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = make_vgaindex(x, y);
  terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_linefeed() {
  terminal_row++;
  terminal_column = 0;
}

int terminal_scan_to_end_of_row(size_t row) {
  size_t column = VGA_WIDTH - 1;
  while (char_from_vgaentry(column, row) == ' ') {
    column--;
  }
  column++;
  if (column >= VGA_WIDTH)
    column--;
  return column;
}

void terminal_backspace() {
  if (terminal_column != 0)
    terminal_column--;
  else if (terminal_row != 0) {
    terminal_row--;
    terminal_column = terminal_scan_to_end_of_row(terminal_row);
    if (terminal_column != VGA_WIDTH - 1) {
      terminal_column--;
    }
  }
  terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
}

bool terminal_handle_special(char c) {
  switch (c) {
  case '\n':
    terminal_linefeed();
    return true;
  case '\b':
    terminal_backspace();
    return true;
  default:
    return false;
  }
}

void terminal_putchar(char c) {
  if (!terminal_handle_special(c)) {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
      terminal_column = 0;
      if (++terminal_row == VGA_HEIGHT) {
        terminal_row = 0;
      }
    }
  }
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
  terminal_update_cursor();
}

void terminal_writestring(const char *data) {
  terminal_write(data, strlen(data));
}
