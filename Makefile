.PHONY: build

all: iso

run: iso
	./qemu.sh

iso: build
	./iso.sh

build:
	./build.sh

clean:
	./clean.sh
