#include <dragon_types.h>
#include <irq.h>
#include <register.h>
#include <attributes.h>
#include <archs.h>


#include <uart.h>

#define __AT_KERNEL_ADDR __attribute__ ((__section__(".ARM.__at_0x80002000")))

extern uint32_t _kernel_bss_begin;
extern uint32_t _kernel_bss_end;

extern void trap_entry(void);
extern void app_main(void);

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

void test_main(void)
{
	asm volatile("la sp, 0x80008000");

	/*
	在U模式执行ecall指令后：
	从U模式切换到S模式
	把当前指令地址保存到sepc寄存器
	设置scause寄存器
	跳转到stvec寄存器保存的地址
	*/
	asm volatile("ecall");
	while(1);
}

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
#if(ARCH == ARCH_RISCV32)
	uint32_t val = 0;
	/* init kernel stack */
	/* kernel end in 0x4000 */
	asm volatile("la sp, 0x80004000");

	// clear bss
	kernel_bss_clear();

	val = read_csr(sstatus);
	//SPP=1 is S Mode, SPP=0 is U Mode
	val = INSERT_FIELD(val, SSTATUS_SPP, 0);
	val = INSERT_FIELD(val, SSTATUS_SPIE, 0);
	write_csr(sstatus, val);

	/* 设置S模式的Exception Program Counter，用于sret跳转 */
	// write_csr(sepc, test_main);
	write_csr(sepc, APP_START_ADDR);
	/* 设置U模式异常向量表入口*/
	// trap_entry的地址在链接脚本的0x80001000
	// write_csr(stvec, 0x80001000);
	write_csr(stvec, trap_entry);

	asm volatile("csrw sscratch, sp");
	/* 切换到U模式 */
	/* 执行完sret,CPU会做以下动作
	CPU会将当前的特权级按照sstatus上的SPP字段来设置为U或者S
	CPU会跳转到sepc寄存器指向的那条指令，然后继续执行 */
	// goto APP_START_ADDR
	asm volatile("sret");
#endif
}

