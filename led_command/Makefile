BBB_KERNEL := /home/thonv/beagle_bone_black/bb-kernel/KERNEL/
TOOLCHAIN := /home/thonv/beagle_bone_black/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin

# Toolchain
PREFIX := arm-linux-gnueabihf-
CC := $(TOOLCHAIN)/$(PREFIX)gcc

all:
	$(CC) -o app app.c gpio.c -I.

clean:
	rm -rf app
