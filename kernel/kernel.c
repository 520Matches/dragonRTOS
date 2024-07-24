#include <dragon_types.h>
#include <irq.h>
#include <attributes.h>

extern uint32_t _kernel_bss_begin;
extern uint32_t _kernel_bss_end;

typedef void (*interrupt_func)(void);

/* static interrupt_func vector_table[] = {
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
}; */

void kernel_bss_clear(void)
{
	uint32_t *p;
	for(p = &_kernel_bss_begin; p <= &_kernel_bss_end;)
	{
		*p++ = 0;
	}
}

__NO_OPTIMIZE void start_kernel(void)
{
	// disable_irq();
	// clear bss
	kernel_bss_clear();

	// enable_irq();
}
