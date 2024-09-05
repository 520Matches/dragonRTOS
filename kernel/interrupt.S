#include <archs.h>

#if(ARCH == ARCH_RISCV32)

.align 4
.global trap_entry
trap_entry:
	/*
	当trap触发的时候，sscratch里面存储了S模式的栈指针(sp)
	这里是把U模式的sp和S模式的sp交换一下
	*/
	/* csrrw sp, sscratch, sp */
	/* 34个寄存器 */
	addi sp, sp, -34

	/* x0是zero寄存器永远是0，不需要保存 */
	sw x1, 1 * POINT_LEN(sp)
	sw x2, 2 * POINT_LEN(sp)
	sw x3, 3 * POINT_LEN(sp)
	sw x4, 4 * POINT_LEN(sp)
	sw x5, 5 * POINT_LEN(sp)
	sw x6, 6 * POINT_LEN(sp)
	sw x7, 7 * POINT_LEN(sp)
	sw x8, 8 * POINT_LEN(sp)
	sw x9, 9 * POINT_LEN(sp)
	sw x10, 10 * POINT_LEN(sp)
	sw x11, 11 * POINT_LEN(sp)
	sw x12, 12 * POINT_LEN(sp)
	sw x13, 13 * POINT_LEN(sp)
	sw x14, 14 * POINT_LEN(sp)
	sw x15, 15 * POINT_LEN(sp)
	sw x16, 16 * POINT_LEN(sp)
	sw x17, 17 * POINT_LEN(sp)
	sw x18, 18 * POINT_LEN(sp)
	sw x19, 19 * POINT_LEN(sp)
	sw x20, 20 * POINT_LEN(sp)
	sw x21, 21 * POINT_LEN(sp)
	sw x22, 22 * POINT_LEN(sp)
	sw x23, 23 * POINT_LEN(sp)
	sw x24, 24 * POINT_LEN(sp)
	sw x25, 25 * POINT_LEN(sp)
	sw x26, 26 * POINT_LEN(sp)
	sw x27, 27 * POINT_LEN(sp)
	sw x28, 28 * POINT_LEN(sp)
	sw x29, 29 * POINT_LEN(sp)
	sw x30, 30 * POINT_LEN(sp)
	sw x31, 31 * POINT_LEN(sp)

	csrr t0, mstatus
	sw t0, 32 * POINT_LEN(sp)
	csrr t0, mepc
	sw t0, 33 * POINT_LEN(sp)
	csrr t0, mcause
	sw t0, 34 * POINT_LEN(sp)

	/* 当产生中断的时候，中断类型码存放再scause或者mcause下 */	
	csrr a0, mcause
	mv a1, sp

	jal trap_handle

	lw t0, 34 * POINT_LEN(sp)
	csrw mcause, t0
	lw t0, 33 * POINT_LEN(sp)
	csrw mepc, t0
	lw t0, 32 * POINT_LEN(sp)
	csrw mstatus, t0

	lw x1, 1 * POINT_LEN(sp)
	lw x2, 2 * POINT_LEN(sp)
	lw x3, 3 * POINT_LEN(sp)
	lw x4, 4 * POINT_LEN(sp)
	lw x5, 5 * POINT_LEN(sp)
	lw x6, 6 * POINT_LEN(sp)
	lw x7, 7 * POINT_LEN(sp)
	lw x8, 8 * POINT_LEN(sp)
	lw x9, 9 * POINT_LEN(sp)
	lw x10, 10 * POINT_LEN(sp)
	lw x11, 11 * POINT_LEN(sp)
	lw x12, 12 * POINT_LEN(sp)
	lw x13, 13 * POINT_LEN(sp)
	lw x14, 14 * POINT_LEN(sp)
	lw x15, 15 * POINT_LEN(sp)
	lw x16, 16 * POINT_LEN(sp)
	lw x17, 17 * POINT_LEN(sp)
	lw x18, 18 * POINT_LEN(sp)
	lw x19, 19 * POINT_LEN(sp)
	lw x20, 20 * POINT_LEN(sp)
	lw x21, 21 * POINT_LEN(sp)
	lw x22, 22 * POINT_LEN(sp)
	lw x23, 23 * POINT_LEN(sp)
	lw x24, 24 * POINT_LEN(sp)
	lw x25, 25 * POINT_LEN(sp)
	lw x26, 26 * POINT_LEN(sp)
	lw x27, 27 * POINT_LEN(sp)
	lw x28, 28 * POINT_LEN(sp)
	lw x29, 29 * POINT_LEN(sp)
	lw x30, 30 * POINT_LEN(sp)
	lw x31, 31 * POINT_LEN(sp)

	/* csrrw sp, sscratch, sp */

	mret
#endif
