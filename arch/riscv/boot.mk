BOOT_DIR := $(ARCH_DIR)/boot

dragon.elf: head.o 
	$(LD) -T $(BOOT_DIR)/boot_linker.ld -o $@ $(BOOT_DIR)/$^

head.o: $(BOOT_DIR)/head.S
	$(GCC) -c $<
	mv head.o $(BOOT_DIR)/

bootclean:
	rm -rf $(BOOT_DIR)/*.o
