// Used for creating GDT segment descriptors in 64-bit integer form.

#include <kernel/gdt.h>

gdt_ptr_t gdt_ptr;
uint64_t gdt_entries[GDT_SIZE];
tss_t tss;

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag) {
  uint64_t descriptor;

  // Create the high 32 bit segment
  descriptor = limit & 0x000F0000; // set limit bits 19:16
  descriptor |= (flag << 8) & 0x00F0FF00; // set type, p, dpl, s, g, d/b, l and avl fields
  descriptor |= (base >> 16) & 0x000000FF; // set base bits 23:16
  descriptor |= base & 0xFF000000;         // set base bits 31:24

  // Shift by 32 to allow for low part of segment
  descriptor <<= 32;

  // Create the low 32 bit segment
  descriptor |= base << 16;         // set base bits 15:0
  descriptor |= limit & 0x0000FFFF; // set limit bits 15:0

  return descriptor;
}

void init_gdt() {
  gdt_ptr.limit = sizeof(uint64_t)*GDT_SIZE - 1;
  gdt_ptr.base = (uint32_t)&gdt_entries;

  gdt_entries[0] = create_descriptor(0, 0, 0);
  gdt_entries[1] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
  gdt_entries[2] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
  gdt_entries[3] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
  gdt_entries[4] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));
  gdt_entries[5] = create_descriptor((uint32_t)&tss, sizeof(tss), (GDT_TSS));

  gdt_flush((uint32_t)&gdt_ptr);

  // load the task state segment
  __asm__("mov 0x28, %ax"); // 0x28 is the address of the task state descriptor
  __asm__("ltr %ax"); // actuall load the tss
}
