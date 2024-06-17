#include <dragon_config.h>
#include <types.h>

extern uint32_t _bss_begin;
extern uint32_t _bss_end;

#define enable_irq() do{asm volatile ("csrw sie, 1");}while(0);
#define disable_irq() do{asm volatile ("csrw sie, zero");}while(0);

typedef void (*entry)(void);

void bss_clear(void)
{
	uint32_t *p;
	for(p = &_bss_begin; p < &_bss_end;)
	{
		*p++ = 0;
	}
}

void boot_main(void)
{
	entry kernel;

	// clear bss
	bss_clear();

	// init interrupt
	enable_irq();

	// goto kernel
	kernel = (entry)KERNEL_START_ADDR;	
	kernel();
}
