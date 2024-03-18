CROSS_COMPILE :=
ARCHS := arm arm64 riscv

ARCH ?= riscv

GCC := $(CROSS_COMPILE)gcc
LD  := $(CROSS_COMPILE)ld
AR  := $(CROSS_COMPILE)ar
NM  := $(CROSS_COMPILE)nm

CUR_DIR := $(shell pwd)

all:
	python3 $(CUR_DIR)/scripts/kconfig.py

menuconfig:
	menuconfig


include $(CUR_DIR)/arch/arch.mk

clean:
