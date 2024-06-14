#include <dragon_config.h>
#include <types.h>

extern uint32_t _bss_begin;
extern uint32_t _bss_end;

void bss_clear(void)
{
	uint32_t *p;
	for(p = &_bss_begin; p < &_bss_end;)
	{
		*p++ = 0;
	}
}

void get_app_start_addr(void)
{
	uint32_t *app_start_addr = (uint32_t *)(BOOT_START_ADDR + BOOT_LEN);
}

void start_kernel(void)
{
	// clear bss
	bss_clear();

	// init interrupt

	// goto app_main
	// app_main();
}
