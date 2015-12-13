AS = i686-elf-as
CC = i686-elf-gcc
CFLAGS = -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LFLAGS = -T linker.ld -std=gnu99 -ffreestanding -O2 -nostdlib
C_SRCS = $(shell find -name "*.c" | sed "s/\.\///g")
HEADERS = $(shell find -name "*.h" | sed "s/\.\///g")
OBJ = ${C_SRCS:.c=.o}
LIBS = -lgcc

all: frackos.iso

run: frackos.iso
	qemu-system-i386 -cdrom frackos.iso

frackos.iso: frackos.bin grub.cfg
	@ mkdir -p isodir/boot/grub
	@ cp frackos.bin isodir/boot/frackos.bin
	@ cp grub.cfg isodir/boot/grub/grub.cfg
	@ grub-mkrescue -d /usr/lib/grub/i386-pc/ -o frackos.iso isodir
	@ rm -rf isodir

frackos.bin: boot.o ${OBJ}
	$(CC) $(LFLAGS) -o $@ $^ $(LIBS)

boot.o: boot.s
	$(AS) $< -o $@

%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.iso ${OBJ} *.bin
