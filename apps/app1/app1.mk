APP_DIR := $(APPS_DIR)/app1

APP1-OBJS := 
APP1-OBJS += dragon_app.o

dragon_app.elf: $(APP1-OBJS)
	$(LD) $(MAP_FLAGS) dragon_app.map -T $(APP_DIR)/app1_linker.ld -o $@ $^
	$(OBJDUMP) -d $@ > dragon_app.asm
	mv *.o $(BUILD_DIR)
	mv *.map $(BUILD_DIR)

dragon_app.o: $(APP_DIR)/app_main.c
	$(GCC) -c $(APPS_CFLAGS) $< -o $@

