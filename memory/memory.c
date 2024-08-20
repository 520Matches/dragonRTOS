#include <dragon_config.h>
#include <dragon_memory.h>

#define HEAP_START	((&_app_bss_begin)++)
#define HEAP_END	(APP_START_ADDR + APP_LEN - APP_STACK_LEN)

// 内存申请的时候4字节对齐
#define MEM_ALIGN	(4)

extern uint32_t _app_bss_begin;


static uint32_t *heap_start = NULL;
static uint32_t heap_len = 0;


void mem_init(void)
{
	// uint32_t *p;
	// for(p = HEAP_START; p <= HEAP_END;)
	// {
	// 	*p++ = 0;
	// }
	heap_start = HEAP_START;
	heap_len = HEAP_END - HEAP_START;
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
