AS = i686-elf-as
CC = i686-elf-gcc
CFLAGS = -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib 
LIBS = -lgcc

all: myos.iso

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

myos.iso: myos.bin
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o myos.iso isodir

myos.bin: boot.o kernel.o
	$(CC) $(LFLAGS) -o $@ $^ $(LIBS)

boot.o: boot.s
	$(AS) $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.iso *.o *.bin isodir
