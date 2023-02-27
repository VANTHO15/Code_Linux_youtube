# Toolchain
TOOLCHAIN := /home/thonv/beagle_bone_black/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin
PREFIX := arm-linux-gnueabihf-

# X
ifeq (${X}, arm)
	CC := $(TOOLCHAIN)/$(PREFIX)gcc
endif

all:
	$(CC) -o hello main.c

clean:
	rm -rf hello
