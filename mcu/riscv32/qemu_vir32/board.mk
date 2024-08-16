MCU-OBJS := 
MCU-OBJS += uart.o

uart.o: $(MCU_DIR)/uart.c
	$(GCC) -c $(APP_CFLAGS) $<

boardclean:
	rm -rf $(MCU_DIR)/*.o
