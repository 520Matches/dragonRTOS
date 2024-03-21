#define STACK_LEN	(4096)

.global _start

_start:
	/* disable all interrupts */
	csrw sie, zero

	/* disable FPU */
	/* TODO */

	/* init stack */
	la sp, STACK_LEN

	/* goto C */
	/* tail main */

