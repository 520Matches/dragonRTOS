#define STACK_LEN	(4096)

.global _start

_start:
	/* disable all interrupts */
	csrw sie, zero

	/* disable FPU */
	/* TODO */

	/* init stack */
	li t0, STACK_LEN
	la sp, t0

	/* goto C */
	/* tail main */

