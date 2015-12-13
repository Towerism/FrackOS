#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/frackos.kernel isodir/boot/frackos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "frackos" {
	multiboot /boot/frackos.kernel
}
EOF
grub-mkrescue -d /usr/lib/grub/i386-pc/ -o frackos.iso isodir
