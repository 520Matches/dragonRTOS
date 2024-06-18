C-FILES := $(wildcard $(KERNEL_DIR)/*.c)

KERNEL-OBJS := 
KERNEL-OBJS += kernel.o

dragon_kernel.elf: $(KERNEL-OBJS)
	$(LD) -T $(KERNEL_DIR)/kernel_linker.ld -o $@ $^
	mv *.o $(BUILD_DIR)

kernel.o: $(KERNEL_DIR)/kernel.c
	$(GCC) -c $(CFLAGS) $<

kernelclean:
	rm -rf $(KERNEL_DIR)/*.o
