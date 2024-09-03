#include <dragon_config.h>
#include <dragon_types.h>
#include <irq.h>
#include <register.h>

extern uint32_t _boot_bss_begin;
extern uint32_t _boot_bss_end;

typedef void (*entry)(void);

static void boot_bss_clear(void)
{
	uint32_t *begin = &_boot_bss_begin;
	uint32_t *end = &_boot_bss_end;
	while(begin <= end)
	{
		*begin++ = 0;
	}
}

// Configure PMP to make all the address space accesable and executable
// static void pmp_open_all_space(void)
// {
//     // Config entry0 addr to all 1s to make the range cover all space
//     asm volatile ("li x6, 0xffffffff":::"x6");
//     asm volatile ("csrw pmpaddr0, x6":::);
//     // Config entry0 cfg to make it NAPOT address mode, and R/W/X okay
//     asm volatile ("li x6, 0x7f":::"x6");
//     asm volatile ("csrw pmpcfg0, x6":::);
// }

/*
static void stimer_start(void)
{
	uint64_t val = 0;
	val = read_csr(0xC81);
	val = val << 32;
	val += read_csr(0xC01);

	val += 100000;
	write_csr(stimecmph, ((val >> 32) & 0xFFFFFFFF));
	write_csr(stimecmp, (val & 0xFFFFFFFF));
}
*/

/*
static void menvcfg_init(void)
{
	// menvcfg的第63位（或menvcfgh的第31位）名为STCE（STimecmp Enable），当设置为1时，启用S模式的STimcmp
	// 当menvcfg中的STCE为零时，试图在M模式以外的模式下访问stimecmp或vstimecmp会引发非法指令常
	uint32_t val = 0;
	val = read_csr(menvcfgh);
	val |= 0x80000000;
	write_csr(menvcfgh, val);
}
*/

void boot_main(void)
{
	uint32_t val = 0;
	// clear bss
	boot_bss_clear();

	// set pmp
	// // It must be NOTED:
	//  //    * In the RISC-V arch, if user mode and PMP supported, then by default if PMP is not configured
	//  //      with valid entries, then user mode cannot access any memory, and cannot execute any instructions.
	//  //    * So if switch to user-mode and still want to continue, then you must configure PMP first
	// pmp_open_all_space();	

	// menvcfg_init();

	// set interrupt vector table
	/* 设置跳转模式为S模式 */
	val = read_csr(mstatus);
	val = INSERT_FIELD(val, MSTATUS_MPP, PRV_M);
	val = INSERT_FIELD(val, MSTATUS_MPIE, 0);
	write_csr(mstatus, val);

	/* 设置M模式的Exception Program Counter，用于mret跳转 */
	write_csr(mepc, KERNEL_START_ADDR);
	/* 设置S模式异常向量表入口*/
	// write_csr(mtvec, KERNEL_START_ADDR);
	/* 关闭S模式的中断*/
	// write_csr(sie, 0);
	/* 关闭S模式的页表转换 */
	// write_csr(satp, 0);

	// 把中断和异常委托给S模式，在U模式下产生中断和异常的时候能够让S模式来处理
	// 在有S模式的情况下需要设置mideleg(中断委托寄存器)和medeleg(异常委托寄存器)
	// write_csr(mideleg, 0xFFFF);
	// write_csr(medeleg, 0xFFFF);

	// 配置定时器
	

	/* 切换到S模式 */
	// goto kernel KERNEL_START_ADDR
	asm volatile("mret");
}
