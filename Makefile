OBJ_DIR := $(shell pwd)

CROSS_COMPILE ?= riscv32-unknown-elf-
ARCHS := arm arm64 riscv

ARCH ?= riscv

GCC := $(CROSS_COMPILE)gcc
LD  := $(CROSS_COMPILE)ld
AR  := $(CROSS_COMPILE)ar
NM  := $(CROSS_COMPILE)nm


ARCH_DIR := $(OBJ_DIR)/arch/$(ARCH)

CFLAGS         := -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
CFLAGS_DEBUG   := $(CFLAGS) -O0 -g
CFLAGS_RELEASE := $(CFLAGS)

BUILD_DIR := $(OBJ_DIR)/build

all: dragon.elf

menuconfig:
	menuconfig
	python3 $(OBJ_DIR)/scripts/kconfig.py


include $(OBJ_DIR)/arch/arch.mk

clean: bootclean
	rm -rf $(OBJ_DIR)/dragon.elf

