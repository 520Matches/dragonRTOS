#include <dragon_types.h>
#include <irq.h>
#include <register.h>

// #define interrupts_register()	do{asm volatile("la t0, %0; csrw 0x307, t0"::"r"(vector_table):);}while(0);

extern uint32_t _kernel_bss_begin;
extern uint32_t _kernel_bss_end;

typedef void (*interrupt_func)(void);

static interrupt_func vector_table[] = {
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
	uint32_t val;
	disable_irq();
	// clear bss
	kernel_bss_clear();

	// set interrupt vector table
	/* 设置跳转模式为S模式 */
	val = read_csr(mstatus);
	val = INSERT_FIELD(val, MSTATUS_MPP, PRV_S);
	val = INSERT_FIELD(val, MSTATUS_MPIE, 0);
	write_csr(mstatus, val);

	/* 设置M模式的Exception Program Counter，用于mret跳转 */
	write_csr(mepc, (uint32_t)vector_table);
	/* 设置S模式异常向量表入口*/
	write_csr(stvec, (uint32_t)vector_table);
	/* 关闭S模式的中断*/
	// write_csr(sie, 0);
	/* 关闭S模式的页表转换 */
	write_csr(satp, 0);

	/* 切换到S模式 */
	asm volatile("mret");

	enable_irq();
}
