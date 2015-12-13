.PHONY: build

all: frackos.iso

run: frackos.iso
	./qemu.sh

iso: build
	./iso.sh

build:
	./build.sh

clean:
	./clean.sh
