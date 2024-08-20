
C-FILES := $(wildcard $(MEMORY_DIR)/*.c)

MEMORY-OBJS := 
MEMORY-OBJS += memory.o


memory.o: $(MEMORY_DIR)/memory.c
	$(GCC) -c $(KERNEL_CFLAGS) $<
	mv *.o $(BUILD_DIR)


memoryclean:
	rm -rf $(MEMORY_DIR)/*.o
