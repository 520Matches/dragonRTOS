#include <archs.h>
#include <dragon_types.h>

#if(ARCH == ARCH_RISCV32)

#define S_SOFTWARE_INT	(1)
#define S_TIMER_INT		(5)
#define S_EXTERNAL_INT	(9)

void trap_handle(uint32_t scause, uint32_t sp)
{
	switch(scause & 0x00000FFF)
	{
		case S_SOFTWARE_INT:
		break;
		case S_TIMER_INT:
		break;
		case S_EXTERNAL_INT:
		break;
		default:
		break;
	}
}

#endif
