OBJ_DIR := $(shell pwd)

CROSS_COMPILE ?= riscv32-unknown-elf-
ARCHS := arm32 arm64 riscv32 riscv64

ARCH ?= riscv32

GCC     := $(CROSS_COMPILE)gcc
LD      := $(CROSS_COMPILE)ld
AR      := $(CROSS_COMPILE)ar
NM      := $(CROSS_COMPILE)nm
OBJCOPY := $(CROSS_COMPILE)objcopy

ARCH_DIR := $(OBJ_DIR)/arch/$(ARCH)
BUILD_DIR := $(OBJ_DIR)/build

INC := -I ./include/ 

# CFLAGS_DEBUG   := $(CFLAGS) -O0 -g
# CFLAGS_RELEASE := $(CFLAGS) -O2

MAP_FLAGS := -Map

BOOT_CFLAGS   := $(INC) -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
KERNEL_CFLAGS := $(INC) -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
APP_CFLAGS    := $(INC) -Wall

BUILD_DIR   := $(OBJ_DIR)/build
SCRIPTS_DIR := $(OBJ_DIR)/scripts
KERNEL_DIR  := $(OBJ_DIR)/kernel

TARGET := dragon.bin

all: dragon_boot.bin dragon_kernel.bin
	rm -rf dragon.bin
	# create zero bin
	dd if=/dev/zero of=dragon.bin bs=1k count=40
	# create 0xFF bin
	# tr '\000' '\377' < /dev/zero | dd of=dragon.bin bs=1k count=40 > /dev/null
	# dd if=/dev/zero bs=1k count=40 | tr '\000' '\377' > dragon.bin
	cat dragon_boot.bin > dragon.bin
	cat dragon_kernel.bin | dd bs=1k seek=8 conv=notrunc of=dragon.bin

dragon_boot.bin   : dragon_boot.elf
	$(OBJCOPY) -O binary $< $@
dragon_kernel.bin : dragon_kernel.elf
	$(OBJCOPY) -O binary $< $@
dragon_app.bin    : dragon_app.elf


menuconfig:
	menuconfig
	python3 $(SCRIPTS_DIR)/kconfig.py
	mv dragon_config.h ./include

include $(OBJ_DIR)/arch/arch.mk
include $(OBJ_DIR)/kernel/kernel.mk


clean: bootclean kernelclean
	rm -rf $(BUILD_DIR)/*.o
	rm -rf $(BUILD_DIR)/*.map
	rm -rf $(OBJ_DIR)/*.elf
	rm -rf $(OBJ_DIR)/*.bin

disclean: clean
	rm -rf $(OBJ_DIR)/include/dragon_config.h

