OBJ_DIR := $(shell pwd)

CROSS_COMPILE ?= riscv32-unknown-elf-
ARCHS := arm32 arm64 riscv32 riscv64

ARCH ?= riscv32
MCU  ?= qemu_vir32

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
MEMORY_DIR  := $(OBJ_DIR)/memory
TASK_DIR  	:= $(OBJ_DIR)/task
MCU_DIR  	:= $(OBJ_DIR)/mcu/$(ARCH)/$(MCU)
APPS_DIR    := $(OBJ_DIR)/apps

# boot size is 8k,kernel size is (16-8)k,dragon size is boot add kernel
BOOT_SIZE   := 8
KERNEL_SIZE := 16
APP_SIZE    :=

KERNEL_APP_SIZE := 24
DRAGON_SIZE     := 40

INC := -I ./include/ -I ./kernel/ -I ./platform/ -I ./common/ -I ./memory/ -I ./task/

# CFLAGS_DEBUG   := $(CFLAGS) -O0 -g
# CFLAGS_RELEASE := $(CFLAGS) -O2

MAP_FLAGS := -Map

BOOT_CFLAGS   := $(INC) -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -O0 -g
KERNEL_CFLAGS := $(INC) -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -O2 -g
APP_CFLAGS    := $(INC) -Wall -fno-builtin -fno-stack-protector -nostartfiles -lc -O2 -g

OBJDUMP_FLAGS := -D -S

define check_dragon_config
	ifeq($(wildcard $(OBJ_DIR)/include/dragon_config.h),)
		@echo "Please do 'make menuconfig' to create dragon_config.h"
	endif
endef

TARGET       := dragon.bin
TARGET_DEBUG := dragon.elf

OBJS-O := $(wildcard $(BUILD_DIR)/*.o)

CORE-OBJS :=

include $(OBJ_DIR)/arch/arch.mk
include $(OBJ_DIR)/kernel/kernel.mk
include $(OBJ_DIR)/mcu/mcu.mk
include $(OBJ_DIR)/memory/mem.mk
include $(OBJ_DIR)/task/task.mk

include $(OBJ_DIR)/apps/apps.mk

all: dragon_boot.bin dragon_core.bin
	rm -rf $(TARGET)
	@# create zero bin
	dd if=/dev/zero of=$(TARGET) bs=1k count=$(DRAGON_SIZE)
	cat dragon_boot.bin > $(TARGET)
	cat dragon_core.bin | dd bs=1k seek=$(BOOT_SIZE) conv=notrunc of=$(TARGET)

dragon_boot.bin   : dragon_boot.elf
	$(OBJCOPY) -O binary $< $@
	mv *.asm $(BUILD_DIR)

dragon_core.bin    : dragon_core.elf
	$(OBJCOPY) -O binary $< $@
	mv *.asm $(BUILD_DIR)

dragon_core.elf: $(CORE-OBJS)
	$(LD) $(MAP_FLAGS) dragon_core.map -T dragon_core_linker.ld -o $@ $^
	$(OBJDUMP) -d $@ > dragon_core.asm
	mv *.o $(BUILD_DIR)
	mv *.map $(BUILD_DIR)

menuconfig:
	menuconfig
	python3 $(SCRIPTS_DIR)/kconfig.py
	mv dragon_config.h ./include


clean: bootclean kernelclean
	rm -rf $(BUILD_DIR)/*.o
	rm -rf $(BUILD_DIR)/*.map
	rm -rf $(BUILD_DIR)/*.asm
	rm -rf $(OBJ_DIR)/*.elf
	rm -rf $(OBJ_DIR)/*.bin

distclean: clean
	rm -rf $(OBJ_DIR)/include/dragon_config.h

