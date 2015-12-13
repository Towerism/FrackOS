AS = i686-elf-as
CC = i686-elf-gcc
CFLAGS = -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib 
LIBS = -lgcc

all: frackos.iso

run: frackos.iso
	qemu-system-i386 -cdrom frackos.iso

frackos.iso: frackos.bin grub.cfg
	mkdir -p isodir/boot/grub
	cp frackos.bin isodir/boot/frackos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o frackos.iso isodir

frackos.bin: boot.o kernel.o
	$(CC) $(LFLAGS) -o $@ $^ $(LIBS)

boot.o: boot.s
	$(AS) $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.iso *.o *.bin isodir
