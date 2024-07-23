OBJ_DIR := $(shell pwd)

CROSS_COMPILE ?= riscv32-unknown-elf-
ARCHS := arm32 arm64 riscv32 riscv64

ARCH ?= riscv32

GCC     := $(CROSS_COMPILE)gcc
LD      := $(CROSS_COMPILE)ld
AR      := $(CROSS_COMPILE)ar
NM      := $(CROSS_COMPILE)nm
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP	:= $(CROSS_COMPILE)objdump

ARCH_DIR    := $(OBJ_DIR)/arch/$(ARCH)
BUILD_DIR   := $(OBJ_DIR)/build
SCRIPTS_DIR := $(OBJ_DIR)/scripts
KERNEL_DIR  := $(OBJ_DIR)/kernel

# boot size is 8k,kernel size is 32k,dragon size is boot add kernel
BOOT_SIZE   := 8
KERNEL_SIZE := 32
DRAGON_SIZE := 40

INC := -I ./include/ 

# CFLAGS_DEBUG   := $(CFLAGS) -O0 -g
# CFLAGS_RELEASE := $(CFLAGS) -O2

MAP_FLAGS := -Map

BOOT_CFLAGS   := $(INC) -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -O0 -g
KERNEL_CFLAGS := $(INC) -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -O2 -g
APP_CFLAGS    := $(INC) -Wall

TARGET := dragon.bin

all: dragon_boot.bin dragon_kernel.bin
	rm -rf dragon.bin
	@# create zero bin
	dd if=/dev/zero of=$(TARGET) bs=1k count=$(DRAGON_SIZE)
	@# create 0xFF bin
	@# tr '\000' '\377' < /dev/zero | dd of=$(TARGET) bs=1k count=40 > /dev/null
	@# dd if=/dev/zero bs=1k count=40 | tr '\000' '\377' > $(TARGET)
	cat dragon_boot.bin > $(TARGET)
	cat dragon_kernel.bin | dd bs=1k seek=$(BOOT_SIZE) conv=notrunc of=$(TARGET)

dragon_boot.bin   : dragon_boot.elf
	$(OBJCOPY) -O binary $< $@
	mv *.asm $(BUILD_DIR)
dragon_kernel.bin : dragon_kernel.elf
	$(OBJCOPY) -O binary $< $@
	mv *.asm $(BUILD_DIR)
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
	rm -rf $(BUILD_DIR)/*.asm
	rm -rf $(OBJ_DIR)/*.elf
	rm -rf $(OBJ_DIR)/*.bin

distclean: clean
	rm -rf $(OBJ_DIR)/include/dragon_config.h

