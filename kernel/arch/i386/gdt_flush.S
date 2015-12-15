
.global gdt_flush
gdt_flush:
  movl 4(%esp), %eax
  lgdt  (%eax)                   // load the gdt
  ljmp $0x08, $gdt_flush_cs      // 0x08 is the selector for the code segment
gdt_flush_cs:
  movw $0x10, %ax                // 0x10 is the selector for the data segment
  movw %ax, %ds                  // initialize selectors
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movw %ax, %ss
  ret
