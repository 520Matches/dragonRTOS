MCU-OBJS := 
MCU-OBJS += uart.o

uart.o: $(MCU_DIR)/uart.c
	$(GCC) -c $(APP_CFLAGS) $<
	mv *.o $(BUILD_DIR)

boardclean:
	rm -rf $(MCU_DIR)/*.o
