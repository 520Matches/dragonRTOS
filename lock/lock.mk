
C-FILES := $(wildcard $(LOCK_DIR)/*.c)

CORE-OBJS += spinlock.o


spinlock.o: $(LOCK_DIR)/spinlock.c
	$(GCC) -c $(APP_CFLAGS) $<

lockclean:
	rm -rf $(LOCK_DIR)/*.o
