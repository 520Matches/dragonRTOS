BOOT_DIR := $(ARCH_DIR)/boot

C-FILES := $(wildcard $(BOOT_DIR)/*.c)
ASM-FILES := $(wildcard $(BOOT_DIR)/*.S)

# FILES-O := $(subst .c,.o,$(C-FILES))
# FILES-O += $(subst .S,.o,$(ASM-FILES))

FILES-O := 
FILES-O += head.o
FILES-O += boot.o

dragon.elf: $(FILES-O)
	$(LD) -T $(BOOT_DIR)/boot_linker.ld -o $@ $^

head.o: $(BOOT_DIR)/head.S
	$(GCC) -c $<

boot.o: $(BOOT_DIR)/boot.c
	$(GCC) -c $(CFLAGS) $<


bootclean:
	rm -rf $(BOOT_DIR)/*.o
