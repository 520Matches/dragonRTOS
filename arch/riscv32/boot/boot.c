#include <dragon_config.h>
#include <dragon_types.h>

extern uint32_t _boot_bss_begin;
extern uint32_t _boot_bss_end;

typedef void (*entry)(void);

void boot_bss_clear(void)
{
	uint32_t *begin = &_boot_bss_begin;
	uint32_t *end = &_boot_bss_end;
	while(begin <= end)
	{
		*begin++ = 0;
	}
}

void boot_main(void)
{
	entry kernel;

	// clear bss
	boot_bss_clear();

	// goto kernel
	kernel = (entry)KERNEL_START_ADDR;	
	kernel();
}
