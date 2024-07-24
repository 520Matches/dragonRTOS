#include <dragon_config.h>
#include <dragon_types.h>
#include <irq.h>
#include <register.h>

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

// Configure PMP to make all the address space accesable and executable
void pmp_open_all_space(){
    // Config entry0 addr to all 1s to make the range cover all space
    asm volatile ("li x6, 0xffffffff":::"x6");
    asm volatile ("csrw pmpaddr0, x6":::);
    // Config entry0 cfg to make it NAPOT address mode, and R/W/X okay
    asm volatile ("li x6, 0x7f":::"x6");
    asm volatile ("csrw pmpcfg0, x6":::);
}

void boot_main(void)
{
	// entry kernel;
	uint32_t val = 0;

	// clear bss
	boot_bss_clear();

	// set pmp
	// // It must be NOTED:
	//  //    * In the RISC-V arch, if user mode and PMP supported, then by default if PMP is not configured
	//  //      with valid entries, then user mode cannot access any memory, and cannot execute any instructions.
	//  //    * So if switch to user-mode and still want to continue, then you must configure PMP first
	pmp_open_all_space();	

	// set interrupt vector table
	/* 设置跳转模式为S模式 */
	val = read_csr(mstatus);
	val = INSERT_FIELD(val, MSTATUS_MPP, PRV_S);
	val = INSERT_FIELD(val, MSTATUS_MPIE, 0);
	write_csr(mstatus, val);

	/* 设置M模式的Exception Program Counter，用于mret跳转 */
	write_csr(mepc, KERNEL_START_ADDR);
	/* 设置S模式异常向量表入口*/
	write_csr(stvec, KERNEL_START_ADDR);
	/* 关闭S模式的中断*/
	// write_csr(sie, 0);
	/* 关闭S模式的页表转换 */
	write_csr(satp, 0);

	/* 切换到S模式 */
	// goto kernel KERNEL_START_ADDR
	asm volatile("mret");
	// goto kernel
	// kernel = (entry)KERNEL_START_ADDR;	
	// kernel();
}
