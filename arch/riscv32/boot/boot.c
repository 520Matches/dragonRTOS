#include <dragon_config.h>
#include <dragon_types.h>

extern uint32_t _boot_bss_begin;
extern uint32_t _boot_bss_end;

#define enable_irq() do{asm volatile ("csrw sie, 1");}while(0);
#define disable_irq() do{asm volatile ("csrw sie, zero");}while(0);

typedef void (*entry)(void);

void boot_bss_clear(void)
{
	uint32_t *begin = &_boot_bss_begin;
	uint32_t *end = &_boot_bss_end;
	while(begin <= end)
	{
		*begin++ = 0;
	}
	// uint32_t *p;
	// for(p = &_boot_bss_begin; p <= &_boot_bss_end;)
	// {
	// 	*p++ = 0;
	// }
}

void boot_main(void)
{
	entry kernel;

	// clear bss
	boot_bss_clear();

	// init interrupt
	enable_irq();

	// goto kernel
	kernel = (entry)KERNEL_START_ADDR;	
	kernel();
}
