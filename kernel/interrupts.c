#include <archs.h>
#include <dragon_types.h>

#if(ARCH == ARCH_RISCV32)

#define S_SOFTWARE_INT	(0x80000001)
#define S_TIMER_INT		(0x80000005)
#define S_EXTERNAL_INT	(0x80000009)

#define S_ACCESS_FAULT_TRAP	(0x00000007)

void trap_handle(uint32_t scause, uint32_t sp)
{
	switch(scause & 0x80000FFF)
	{
		case S_SOFTWARE_INT:
		break;
		case S_TIMER_INT:
		break;
		case S_EXTERNAL_INT:
		break;
		case S_ACCESS_FAULT_TRAP:

		break;
		default:
		break;
	}
}

#endif
