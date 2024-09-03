#include <dragon_config.h>
#include <dragon_memory.h>

#define HEAP_START	(&_core_bss_end)
#define HEAP_END	(APP_START_ADDR + APP_LEN - APP_MAIN_STACK_LEN)

// 内存申请的时候4字节对齐
#define MEM_ALIGN	(4)

extern uint32_t _core_bss_end;


static uint32_t *heap_start = NULL;
static uint32_t heap_len = 0;


void mem_init(void)
{
	heap_start = HEAP_START;
	heap_start++;
	heap_len = HEAP_END - (uint32_t)heap_start;
}

void* memalloc(uint32_t size)
{
	uint32_t *p = heap_start;
	uint32_t num = 0;
	if((size == 0) || (size > heap_len))
	{
		return NULL;
	}
	size = (size / MEM_ALIGN) * MEM_ALIGN;
	num = size / MEM_ALIGN;

	heap_start += num;
	heap_len -= size;

	return (void *)p;
}
