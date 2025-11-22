# CORE-OBJS += kernel.o
# CORE-OBJS += interrupt.o
# CORE-OBJS += interrupts.o
# CORE-OBJS += systick.o
# CORE-OBJS += task.o
# CORE-OBJS += scheduler.o
#
#
# kernel.o: $(KERNEL_DIR)/kernel.c
# 	$(GCC) -c $(KERNEL_CFLAGS) $<
#
# interrupt.o: $(KERNEL_DIR)/interrupt.S
# 	$(GCC) -c $(BOOT_CFLAGS) $<
#
# interrupts.o: $(KERNEL_DIR)/interrupts.c
# 	$(GCC) -c $(KERNEL_CFLAGS) $<
#
# context_switch.o: $(KERNEL_DIR)/context_switch.S
# 	$(GCC) -c $(BOOT_CFLAGS) $<
#
# systick.o: $(KERNEL_DIR)/systick.c
# 	$(GCC) -c $(KERNEL_CFLAGS) $<
#
# task.o: $(KERNEL_DIR)/task.c
# 	$(GCC) -c $(KERNEL_CFLAGS) $<
#
# scheduler.o: $(KERNEL_DIR)/scheduler.c
# 	$(GCC) -c $(KERNEL_CFLAGS) $<

KERNEL_C_SRCS := $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_ASM_SRCS := $(wildcard $(KERNEL_DIR)/*.S)

# 将源文件转换为对应的 .o 文件（去掉路径前缀）
KERNEL_C_OBJS := $(notdir $(KERNEL_C_SRCS:.c=.o))
KERNEL_ASM_OBJS := $(notdir $(KERNEL_ASM_SRCS:.S=.o))

# 将所有 .o 文件添加到 CORE-OBJS
CORE-OBJS += $(KERNEL_C_OBJS)
CORE-OBJS += $(KERNEL_ASM_OBJS)

# 编译规则 - 指定源文件路径
%.o: $(KERNEL_DIR)/%.c
	$(GCC) $(KERNEL_CFLAGS) -c $< -o $@

%.o: $(KERNEL_DIR)/%.S
	$(GCC) $(KERNEL_CFLAGS) -c $< -o $@


# CORE-OBJS += $(patsubst %.c,%.o,$(wildcard *.c))
# CORE-OBJS += $(patsubst %.S,%.o,$(wildcard *.S))
#
# # 编译规则
# %.o: %.c
# 	$(GCC) $(KERNEL_CFLAGS) -c $< -o $@
#
# %.o: %.S
# 	$(GCC) $(KERNEL_CFLAGS) -c $< -o $@

kernelclean:
	rm -rf $(KERNEL_DIR)/*.o
