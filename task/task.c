#include <task.h>
#include <dragon_memory.h>

#define TASK_MAX_NUM	(64)

static task_handle_t* task_array[TASK_MAX_NUM] = {NULL};
static int task_index = 0;
static int current_task_index = 0;

static task_handle_t *current_task = NULL;

task_handle_t* task_create(const char* const name, uint32_t stack_size, task_func entry, void *args, task_prority_t prority)
{
	task_handle_t *task = NULL;
	if(stack_size == 0)
	{
		return NULL;
	}
	if(task_index >= TASK_MAX_NUM)
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
	task->args = args;
	task->prority = prority;
	task->status = TASK_STATUS_READY;

	if(task_index < TASK_MAX_NUM)
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
	int find_flag = 0;
	task_handle_t *handle = task_array[current_task_index];
	task_handle_t *current_handle = task_array[current_task_index];
	if(task_index <= 1)
	{
		return;	
	}
	for(int i = current_task_index + 1; i < task_index; i++)
	{
		if((task_array[i] != NULL) && (task_array[i]->status == TASK_STATUS_READY) && (task_array[i]->prority >= handle->prority))
		{
			handle = task_array[i];
			current_task_index = i;
			find_flag = 1;
		}
	}
	for(int i = 0; i < current_task_index; i++)
	{
		if((task_array[i] != NULL) && (task_array[i]->status == TASK_STATUS_READY) && (task_array[i]->prority >= handle->prority))
		{
			handle = task_array[i];
			current_task_index = i;
			find_flag = 1;
		}
	}
	if(find_flag == 0)
	{
		return;
	}
	current_handle->status = TASK_STATUS_READY;
	handle->status = TASK_STATUS_RUNNING;
	//汇编切换任务
	//TODO
}

void task_scheduler_start(void)
{
	task_handle_t *handle;
	if((current_task == NULL) && (task_index == 0))
	{
		return;
	}
	//计算优先级最高的就绪态任务
	if((current_task != NULL) && (task_index == 1))
	{
		//布置堆栈
		current_task->status = TASK_STATUS_RUNNING;
		current_task->func(current_task->args);
		return;
	}
	for(int i = 0; i < task_index; i++)
	{
		handle = task_array[i];
		if((handle->status == TASK_STATUS_READY) && (handle->prority > current_task->prority))
		{
			current_task = handle;
			current_task_index = i;
		}
	}
	//
	//执行任务
	if(current_task != NULL)
	{
		//布置堆栈
		//跳转到任务函数
		current_task->status = TASK_STATUS_RUNNING;
		current_task->func(current_task->args);
	}
}
