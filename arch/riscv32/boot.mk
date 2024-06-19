BOOT_DIR := $(ARCH_DIR)/boot

C-FILES := $(wildcard $(BOOT_DIR)/*.c)
ASM-FILES := $(wildcard $(BOOT_DIR)/*.S)

# BOOT-OBJS := $(subst .c,.o,$(C-FILES))
# BOOT-OBJS += $(subst .S,.o,$(ASM-FILES))

BOOT-OBJS := 
BOOT-OBJS += head.o
BOOT-OBJS += boot.o

dragon_boot.elf: $(BOOT-OBJS)
	$(LD) $(MAP_FLAGS) boot.map -T $(BOOT_DIR)/boot_linker.ld -o $@ $^
	mv *.o $(BUILD_DIR)
	mv *.map $(BUILD_DIR)

head.o: $(BOOT_DIR)/head.S
	$(GCC) -c $(BOOT_CFLAGS) $<

boot.o: $(BOOT_DIR)/boot.c
	$(GCC) -c $(BOOT_CFLAGS) $<

bootclean:
	rm -rf $(BOOT_DIR)/*.o
