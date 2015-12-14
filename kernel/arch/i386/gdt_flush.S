.global gdt_flush
gdt_flush:
  cli                           # disable interrupts
  movl 4(%esp), %eax            # get pointer to gdt, passed as argument
  lgdt (%eax)                   # load the gdt
  mov 0x10, %ax                 # 0x10 is the address of the data segment
  mov %ax, %ds                  # initialize selectors
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss
  # long jump to 0x08:.flush, 0x08 is the address of the code segment
  mov gdt_flush_done, %ebx
  movw $0x08, (code_address_offset)
  movw %ebx, (code_address_segment)
  ljmp *(code_address_offset)
gdt_flush_done: 
  sti                           # re-enable interrupts
  ret

.code_address_data:
code_address_offset:   .word 0
code_address_segment:  .word 0
