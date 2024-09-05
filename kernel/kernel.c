#include <dragon_types.h>
#include <irq.h>
#include <register.h>
#include <attributes.h>
#include <archs.h>

#include <dragon_memory.h>
#include <systick.h>
#include <uart.h>

// #define __AT_KERNEL_ADDR __attribute__ ((__section__(".ARM.__at_0x80002000")))


extern uint32_t _core_bss_begin;
extern uint32_t _core_bss_end;

extern void trap_entry(void);
extern void app_main(void);

// void test_main(void)
// {
// 	asm volatile("la sp, 0x80008000");
//
// 	/*
// 	在U模式执行ecall指令后：
// 	从U模式切换到S模式
// 	把当前指令地址保存到sepc寄存器
// 	设置scause寄存器
// 	跳转到stvec寄存器保存的地址
// 	*/
// 	// asm volatile("ecall");
// 	while(1);
// }

// static void stimer_restart(void)
// {
// 	uint64_t val = 0;
// 	val = read_csr(0xC81);
// 	val = val << 32;
// 	val += read_csr(0xC01);
//
// 	val += 100000;
// 	write_csr(stimecmph, ((val >> 32) & 0xFFFFFFFF));
// 	write_csr(stimecmp, (val & 0xFFFFFFFF));
// }

static void core_bss_clear(void)
{
	uint32_t *p;
	for(p = &_core_bss_begin; p <= &_core_bss_end;)
	{
		*p++ = 0;
	}
}

static inline void stack_init(void)
{
#if(ARCH == ARCH_RISCV32)
	asm volatile("la sp, 0x80008000");
#endif
}

static inline void trap_init(void)
{
#if(ARCH == ARCH_RISCV32)
	/* 设置S模式的Exception Program Counter，用于sret跳转 */
	// write_csr(sepc, test_main);
	// write_csr(sepc, APP_START_ADDR);
	/* 设置异常向量表入口*/
	write_csr(mtvec, trap_entry);
#endif
}

__NO_OPTIMIZE void start_kernel(void)
{
	/* init kernel stack */
	/* kernel end in 0x4000 */
	stack_init();

	// clear bss
	core_bss_clear();
/*
	val = read_csr(sstatus);
	//SPP=1 is S Mode, SPP=0 is U Mode
	val = INSERT_FIELD(val, SSTATUS_SPP, 0);
	val = INSERT_FIELD(val, SSTATUS_SPIE, 0);
	write_csr(sstatus, val);
*/
	trap_init();

	mem_init();

	systick_init();

	while(1);
	app_main();

	// 保存S模式下的sp
	// asm volatile("csrw sscratch, sp");

	/* 切换到U模式 */
	/* 执行完sret,CPU会做以下动作
	CPU会将当前的特权级按照sstatus上的SPP字段来设置为U或者S
	CPU会跳转到sepc寄存器指向的那条指令，然后继续执行 */
	// goto APP_START_ADDR
	// asm volatile("sret");
}

