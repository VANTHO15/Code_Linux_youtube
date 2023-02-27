# Paths
BBB_KERNEL := /home/thonv/beagle_bone_black/bb-kernel/KERNEL/
TOOLCHAIN := /home/thonv/beagle_bone_black/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin

# Toolchain
PREFIX := arm-linux-gnueabihf-

all:
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN)/$(PREFIX) -C $(BBB_KERNEL) M=$(PWD) modules
	
clean:
	make -C $(BBB_KERNEL) M=$(PWD) clean
 