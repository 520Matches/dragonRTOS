BOOT_DIR := $(ARCH_DIR)/boot

BOOT-O := head.o
BOOT-O += boot.o

dragon.elf: $(BOOT-O)
	$(LD) -T $(BOOT_DIR)/boot_linker.ld -o $@ $^

head.o: $(BOOT_DIR)/head.S
	$(GCC) -c $<

boot.o: $(BOOT_DIR)/boot.c
	$(GCC) -c $<


bootclean:
	rm -rf $(BOOT_DIR)/*.o
