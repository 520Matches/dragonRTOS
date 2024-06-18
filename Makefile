OBJ_DIR := $(shell pwd)

CROSS_COMPILE ?= riscv32-unknown-elf-
ARCHS := arm32 arm64 riscv32 riscv64

ARCH ?= riscv32

GCC := $(CROSS_COMPILE)gcc
LD  := $(CROSS_COMPILE)ld
AR  := $(CROSS_COMPILE)ar
NM  := $(CROSS_COMPILE)nm

ARCH_DIR := $(OBJ_DIR)/arch/$(ARCH)
BUILD_DIR := $(OBJ_DIR)/build

INC := -I ./include/ 

# CFLAGS_DEBUG   := $(CFLAGS) -O0 -g
# CFLAGS_RELEASE := $(CFLAGS) -O2

BOOT_CFLAGS   := $(INC) -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
KERNEL_CFLAGS := $(INC) -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
APP_CFLAGS    := $(INC) -Wall

BUILD_DIR   := $(OBJ_DIR)/build
SCRIPTS_DIR := $(OBJ_DIR)/scripts
KERNEL_DIR  := $(OBJ_DIR)/kernel

dragon_boot   : dragon_boot.elf
dragon_kernel : dragon_kernel.elf
dragon_app    : dragon_app.elf

all: dragon_boot.elf dragon_kernel.elf

menuconfig:
	menuconfig
	python3 $(SCRIPTS_DIR)/kconfig.py
	mv dragon_config.h ./include

include $(OBJ_DIR)/arch/arch.mk
include $(OBJ_DIR)/kernel/kernel.mk


clean: bootclean
	rm -rf $(BUILD_DIR)/*.o
	rm -rf $(OBJ_DIR)/dragon_boot.elf
	rm -rf $(OBJ_DIR)/dragon_kernel.elf

disclean: clean
	rm -rf $(OBJ_DIR)/include/dragon_config.h

