OBJ_DIR := $(shell pwd)

include $(OBJ_DIR)/config.mk

# ARCHS := arm32 arm64 riscv32 riscv64

# ARCH ?= riscv32
MCU  ?= qemu_vir32
# MCU  ?= sifive_e31

GCC     := $(CONFIG_CROSS_COMPILE)gcc
LD      := $(CONFIG_CROSS_COMPILE)ld
AR      := $(CONFIG_CROSS_COMPILE)ar
NM      := $(CONFIG_CROSS_COMPILE)nm
OBJCOPY := $(CONFIG_CROSS_COMPILE)objcopy
OBJDUMP	:= $(CONFIG_CROSS_COMPILE)objdump

ARCH_DIR    := $(OBJ_DIR)/arch/$(ARCH)
BUILD_DIR   := $(OBJ_DIR)/build
SCRIPTS_DIR := $(OBJ_DIR)/scripts
KERNEL_DIR  := $(OBJ_DIR)/kernel
MEMORY_DIR  := $(OBJ_DIR)/memory
TASK_DIR  	:= $(OBJ_DIR)/task
LOCK_DIR  	:= $(OBJ_DIR)/lock
MCU_DIR  	:= $(OBJ_DIR)/mcu/$(ARCH)/$(MCU)
APPS_DIR    := $(OBJ_DIR)/apps

# boot size is 8k,kernel size is (16-8)k,dragon size is boot add kernel
BOOT_SIZE   := 8
KERNEL_SIZE := 16
APP_SIZE    :=

STACK_SIZE := $(shell grep -w STACK_SIZE ./include/dragon_config.h | awk '{print $$3}')


KERNEL_APP_SIZE := 24
DRAGON_SIZE     := 40

INC := -I ./include/ -I ./kernel/ -I ./platform/ -I ./common/ -I ./memory/ -I ./task/ -I ./mcu/ -I ./lock/

# CFLAGS_DEBUG   := $(CFLAGS) -O0 -g
# CFLAGS_RELEASE := $(CFLAGS) -O2

MAP_FLAGS := -Map
# MAP_FLAGS := -Wl,-Map=dragon_core.map

# # 基础配置
# -march=rv32i      # 只有基础整数指令
# -march=rv32im     # 基础整数 + 乘除法（最常用）
# -march=rv32ima    # + 原子操作
# -march=rv32imaf   # + 单精度浮点
# -march=rv32imafd  # + 双精度浮点（完整G系列）
#
# # 其他扩展
# -march=rv32imc    # + 压缩指令（代码密度优化）
# -march=rv32imac   # 原子操作 + 压缩指令
#
# # 32位架构
# -mabi=ilp32     # int, long, pointer都是32位（最常用）
# -mabi=ilp32f    # 硬件浮点调用约定
# -mabi=ilp32d    # 双精度硬件浮点调用约定
#
# # 64位架构  
# -mabi=lp64      # long和pointer是64位
# -mabi=lp64f     # 64位+硬件浮点
# -mabi=lp64d     # 64位+双精度浮点

BOOT_CFLAGS   := $(INC) -Wall -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -O0 -g
KERNEL_CFLAGS := $(INC) -Wall -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -O2 -g
APP_CFLAGS    := $(INC) -Wall -fno-builtin -fno-stack-protector -nostartfiles -Xlinker --defsym=__stack_size=$(STACK_SIZE) -lc -O2 -g
# APP_CFLAGS    := $(INC) -Wall -O2 -g
# 通过链接器选项传递符号
LDFLAGS += -Xlinker --defsym=__stack_size=$(STACK_SIZE)
# LIBS := -lgcc -lc -Wl,-Map=dragon_core.map
LIBS := -lgcc -lc

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
# include $(OBJ_DIR)/task/task.mk
# include $(OBJ_DIR)/lock/lock.mk

# include $(OBJ_DIR)/apps/apps.mk

# 根据 ARCH 选择链接脚本
ifeq ($(ARCH),arm32)
LINKER_SCRIPT = ./ldfile/dragon_arm32_linker.ld
else ifeq ($(ARCH),riscv32)
LINKER_SCRIPT = ./ldfile/dragon_riscv32_linker.ld
else
LINKER_SCRIPT = default_linker.ld
endif

# LIBGCC_PATH := $(shell dirname $(shell $(GCC) -print-libgcc-file-name))
# LIBC_PATH := $(shell dirname $(shell $(GCC) -print-file-name=libc.a))

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
	$(GCC) $(APP_CFLAGS) -T $(LINKER_SCRIPT) -o $@ $^ $(LIBS) -Wl,-Map=dragon_core.map
	# $(LD) $(MAP_FLAGS) dragon_core.map -T $(LINKER_SCRIPT) -o $@ $^ -L$(LIBGCC_PATH) -lgcc -L$(LIBC_PATH) -lc
	$(OBJDUMP) -d $@ > dragon_core.asm
	mv *.o $(BUILD_DIR)
	mv *.map $(BUILD_DIR)

menuconfig:
	menuconfig
	python3 $(SCRIPTS_DIR)/kconfig.py
	python3 $(SCRIPTS_DIR)/config2mk.py
	mv dragon_config.h ./include


clean: bootclean kernelclean
	rm -rf ./*.o
	rm -rf $(BUILD_DIR)/*.o
	rm -rf $(BUILD_DIR)/*.map
	rm -rf $(BUILD_DIR)/*.asm
	rm -rf $(OBJ_DIR)/*.elf
	rm -rf $(OBJ_DIR)/*.bin

distclean: clean
	rm -rf $(OBJ_DIR)/include/dragon_config.h

