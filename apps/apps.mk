APP_DIR := $(APPS_DIR)/app1
#
# APP-OBJS := 
# APP-OBJS += dragon_app.o
#
# APP-OBJS += uart.o
# APP-OBJS += memory.o
# APP-OBJS += task.o
#
# dragon_app.elf: $(APP-OBJS)
# 	$(LD) --no-warn-rwx-segments $(MAP_FLAGS) dragon_app.map -T $(APP_DIR)/app1_linker.ld -o $@ $^
# 	$(OBJDUMP) -d $@ > dragon_app.asm
# 	mv *.o $(BUILD_DIR)
# 	mv *.map $(BUILD_DIR)


include $(APPS_DIR)/app1/app1.mk
