
C-FILES := $(wildcard $(MEMORY_DIR)/*.c)

CORE-OBJS += memory.o
# CORE-OBJS += heap.o
CORE-OBJS += tlsf.o


memory.o: $(MEMORY_DIR)/memory.c
	$(GCC) -c $(APP_CFLAGS) $<

# heap.o: $(MEMORY_DIR)/heap.c
# 	$(GCC) -c $(APP_CFLAGS) $<

# tlsf.o: $(MEMORY_DIR)/tlsf.c
# 	$(GCC) -c $(APP_CFLAGS) $<

tlsf.o: $(MEMORY_DIR)/tlsf.c
	$(GCC) -c $< $(LIBS)

memoryclean:
	rm -rf $(MEMORY_DIR)/*.o
