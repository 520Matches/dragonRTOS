
C-FILES := $(wildcard $(MEMORY_DIR)/*.c)

MEMORY-OBJS := 
MEMORY-OBJS += memory.o


memory.o: $(MEMORY_DIR)/memory.c
	$(GCC) -c $(APP_CFLAGS) $<

memoryclean:
	rm -rf $(MEMORY_DIR)/*.o
