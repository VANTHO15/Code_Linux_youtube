# Hello world kernel module
# Paths
BBB_KERNEL := /home/thonv/beagle_bone_black/bb-kernel/KERNEL/
TOOLCHAIN := /home/thonv/beagle_bone_black/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin

# Toolchain
PREFIX := arm-linux-gnueabihf-
CC := $(TOOLCHAIN)/$(PREFIX)gcc

all:
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN)/$(PREFIX) -C $(BBB_KERNEL) M=$(PWD) modules
	$(CC) -o app usr_app.c

clean:
	make -C $(BBB_KERNEL) M=$(PWD) clean
	rm -rf app
