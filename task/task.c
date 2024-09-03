#include <task.h>
#include <dragon_memory.h>

static task_handle_t* task_array[TASK_PRORITY_MAX] = {NULL};
static int task_index = 0;

static task_handle_t *current_task = NULL;

task_handle_t* task_create(const char* const name, uint32_t stack_size, task_func entry, task_prority_t prority)
{
	task_handle_t *task = NULL;
	if(stack_size == 0)
	{
		return NULL;
	}
	if(task_index > TASK_PRORITY_MAX)
	{
		return NULL;
	}
	if((prority > TASK_PRORITY_MAX) || (prority < TASK_PRORITY_MIN))
	{
		return NULL;
	}
	task = memalloc(sizeof(task_handle_t));
	if(task == NULL)
	{
		return NULL;
	}
	task->stack = (uint32_t *)memalloc(stack_size);
	if(task->stack == NULL)
	{
		return NULL;
	}
	task->stack_size = stack_size;
	task->func = entry;
	task->prority = prority;

	if(task_index <= TASK_PRORITY_MAX)
	{
		task_array[task_index++] = task;
	}

	if(current_task == NULL)
	{
		current_task = task;
	}

	return task;
}

void task_scheduler(void)
{
}
