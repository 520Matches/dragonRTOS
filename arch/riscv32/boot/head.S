#define STACK_LEN	(4096)

.section ".text.boot"

.global _start

_start:
	/* disable all interrupts */
	csrw sie, zero

	/* flush the instruction cache */
	fence.i
	
	/* disable FPU */
	/* TODO */

	/* reset all registers except ra, a0, a1 */
	/* call reset_regs */

	/* init stack */
	la sp, stacks_start
	li t0, STACK_LEN
	add sp, sp, t0

	/* enable all interrupts */	
	csrw sie, 1

	/* goto C */
	tail boot_main


/* reset all registers */
reset_regs:
	li	sp, 0
	li	gp, 0
	li	tp, 0
	li	t0, 0
	li	t1, 0
	li	t2, 0
	li	s0, 0
	li	s1, 0
	li	a2, 0
	li	a3, 0
	li	a4, 0
	li	a5, 0
	li	a6, 0
	li	a7, 0
	li	s2, 0
	li	s3, 0
	li	s4, 0
	li	s5, 0
	li	s6, 0
	li	s7, 0
	li	s8, 0
	li	s9, 0
	li	s10, 0
	li	s11, 0
	li	t3, 0
	li	t4, 0
	li	t5, 0
	li	t6, 0
	ret

.section .data
.global stacks_start
stacks_start:
	.skip 1024
