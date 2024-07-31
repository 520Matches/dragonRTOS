C-FILES := $(wildcard $(KERNEL_DIR)/*.c)

KERNEL-OBJS := 
KERNEL-OBJS += kernel.o
KERNEL-OBJS += interrupt.o

dragon_kernel.elf: $(KERNEL-OBJS)
	$(LD) $(MAP_FLAGS) kernel.map -T $(KERNEL_DIR)/kernel_linker.ld -o $@ $^
	$(OBJDUMP) -d $@ > dragon_kernel.asm
	mv *.o $(BUILD_DIR)
	mv *.map $(BUILD_DIR)

kernel.o: $(KERNEL_DIR)/kernel.c
	$(GCC) -c $(KERNEL_CFLAGS) $<

interrupt.o: $(BOOT_DIR)/interrupt.S
	$(GCC) -c $(BOOT_CFLAGS) $<

kernelclean:
	rm -rf $(KERNEL_DIR)/*.o
