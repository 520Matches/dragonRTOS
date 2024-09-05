CORE-OBJS += kernel.o
CORE-OBJS += interrupt.o
CORE-OBJS += interrupts.o
CORE-OBJS += systick.o


kernel.o: $(KERNEL_DIR)/kernel.c
	$(GCC) -c $(KERNEL_CFLAGS) $<

interrupt.o: $(KERNEL_DIR)/interrupt.S
	$(GCC) -c $(BOOT_CFLAGS) $<

interrupts.o: $(KERNEL_DIR)/interrupts.c
	$(GCC) -c $(KERNEL_CFLAGS) $<

systick.o: $(KERNEL_DIR)/systick.c
	$(GCC) -c $(KERNEL_CFLAGS) $<

kernelclean:
	rm -rf $(KERNEL_DIR)/*.o
