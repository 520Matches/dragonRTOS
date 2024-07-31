#include <dragon_types.h>
#include <irq.h>
#include <register.h>
#include <attributes.h>

extern uint32_t _kernel_bss_begin;
extern uint32_t _kernel_bss_end;

extern void trap_entry(void);

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
	uint32_t val = 0;
	// disable_irq();
	// clear bss
	kernel_bss_clear();

	val = read_csr(sstatus);
	//SPP=1 is S Mode, SPP=0 is U Mode
	val = INSERT_FIELD(val, SSTATUS_SPP, 1);
	val = INSERT_FIELD(val, SSTATUS_SPIE, 0);
	write_csr(sstatus, val);

	/* 设置S模式的Exception Program Counter，用于sret跳转 */
	write_csr(sepc, trap_entry);
	/* 设置U模式异常向量表入口*/
	write_csr(stvec, trap_entry);

	/* 切换到U模式 */
	/* 执行完sret,CPU会做以下动作
	CPU会将当前的特权级按照sstatus上的SPP字段来设置为U或者S
	CPU会跳转到sepc寄存器指向的那条指令，然后继续执行 */
	// goto trap_entry
	asm volatile("sret");

	// enable_irq();
}
