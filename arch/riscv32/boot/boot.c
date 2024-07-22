#include <dragon_config.h>
#include <dragon_types.h>


#define __WEAK	__attribute__((weak))

extern uint32_t _boot_bss_begin;
extern uint32_t _boot_bss_end;

#define enable_irq() do{asm volatile ("csrw sie, 1");}while(0);
#define disable_irq() do{asm volatile ("csrw sie, zero");}while(0);

typedef void (*entry)(void);
typedef void (*int_func)(void);

__WEAK void s_software_handle(void);
__WEAK void m_software_handle(void);
__WEAK void s_timer_handle(void);
__WEAK void m_timer_handle(void);
__WEAK void s_exit_handle(void);
__WEAK void m_exit_handle(void);

static int_func vector_table[] = {
	NULL,
	s_software_handle,
	NULL,
	m_software_handle,
	NULL,
	s_timer_handle,
	NULL,
	m_timer_handle,
	NULL,
	s_exit_handle,
	NULL,
	m_exit_handle,
	NULL,
	NULL,
};

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

	// set interrupt vector table
	
	// init interrupt
	// enable_irq();


	// goto kernel
	kernel = (entry)KERNEL_START_ADDR;	
	kernel();
}
