#ifndef __TASK_H
#define __TASK_H

#include <dragon_types.h>

typedef void (*task_func)(void *arg);

typedef struct {
	//堆栈指针
	uint32_t *stack;
}task_handle_t;

int task_create(const char* const name, uint32_t stack_size, task_func entry, uint8_t prority);


#endif
