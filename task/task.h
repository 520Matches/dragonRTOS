#ifndef __TASK_H
#define __TASK_H

#include <dragon_types.h>

typedef void (*task_func)(void *arg);

typedef enum {
	TASK_PRORITY_MIN = 0,
	TASK_PRORITY_1   = 1,
	TASK_PRORITY_2   = 2,
	TASK_PRORITY_3   = 3,
	TASK_PRORITY_4   = 4,
	TASK_PRORITY_5   = 5,
	TASK_PRORITY_6   = 6,
	TASK_PRORITY_7   = 7,
	TASK_PRORITY_8   = 8,
	TASK_PRORITY_9   = 9,
	TASK_PRORITY_10  = 10,
	TASK_PRORITY_11  = 11,
	TASK_PRORITY_12  = 12,
	TASK_PRORITY_13  = 13,
	TASK_PRORITY_14  = 14,
	TASK_PRORITY_MAX = 15,
}task_prority_t;

typedef enum {
	TASK_STATUS_DEAD = 0,
	TASK_STATUS_READY = 1,
	TASK_STATUS_RUNNING = 2,
	TASK_STATUS_BLOCK = 3,
	TASK_STATUS_STOP = 4,
	TASK_STATUS_MAX = 5,
}task_status_t;

typedef struct {
	//堆栈指针
	uint32_t *stack;

	uint32_t stack_size;
	uint8_t prority;
	task_func func;
	void *args;
	task_status_t status;
}task_handle_t;

task_handle_t* task_create(const char* const name, uint32_t stack_size, task_func entry, void *args, task_prority_t prority);


#endif
