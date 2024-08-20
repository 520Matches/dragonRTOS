TASK-OBJS := 
TASK-OBJS += task.o


task.o: $(TASK_DIR)/task.c
	$(GCC) -c $(APP_CFLAGS) $<
