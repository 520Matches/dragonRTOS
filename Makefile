CUR_DIR := $(shell pwd)

CROSS_COMPILE ?= ~/software/riscv64/bin/riscv64-unknown-linux-gnu-
ARCHS := arm arm64 riscv

ARCH ?= riscv

GCC := $(CROSS_COMPILE)gcc
LD  := $(CROSS_COMPILE)ld
AR  := $(CROSS_COMPILE)ar
NM  := $(CROSS_COMPILE)nm


BOOT_DIR := $(CUR_DIR)/arch/$(ARCH)/boot

CFLAGS         := -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
CFLAGS_DEBUG   := $(CFLAGS) -O0 -g
CFLAGS_RELEASE := $(CFLAGS)

all: dragon.img
	make -C $(BOOT_DIR)

menuconfig:
	menuconfig
	python3 $(CUR_DIR)/scripts/kconfig.py


include $(CUR_DIR)/arch/arch.mk

clean:
