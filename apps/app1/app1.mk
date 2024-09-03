
CORE-OBJS += app_main.o

app_main.o: $(APP_DIR)/app_main.c
	$(GCC) -c $(APP_CFLAGS) $< -o $@
