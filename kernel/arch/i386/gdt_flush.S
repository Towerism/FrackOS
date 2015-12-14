.global gdt_flush
gdt_flush:
  cli                           # disable interrupts
  movl 4(%esp), %eax            # get pointer to GDT, passed as argument
  lgdt (%eax)                   # load the gdt
  ljmp $0x08, $gdt_reload_registers # 0x08 is the selector for the code segment
gdt_reload_registers: 
  mov 0x10, %ax                 # 0x10 is the selector for the data segment
  mov %ax, %ds                  # initialize selectors
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss

  sti                           # re-enable interrupts
  ret
