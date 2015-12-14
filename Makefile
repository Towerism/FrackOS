.PHONY: build

all: iso

run: iso
	./qemu.sh

iso: build
	./iso.sh

build: config
	./build.sh

config:
	./config.sh

clean:
	./clean.sh
