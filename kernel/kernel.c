#include <dragon_types.h>

extern uint32_t _kernel_bss_begin;
extern uint32_t _kernel_bss_end;

void kernel_bss_clear(void)
{
	uint32_t *p;
	for(p = &_kernel_bss_begin; p <= &_kernel_bss_end;)
	{
		*p++ = 0;
	}
}

void start_kernel(void)
{
	// set interrupt vector table
	
	// clear bss
	kernel_bss_clear();
}
