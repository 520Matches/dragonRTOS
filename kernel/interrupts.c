#include <archs.h>
#include <dragon_types.h>
#include <systick.h>

#if(ARCH == ARCH_RISCV32)

#define S_SOFTWARE_INT	(0x80000001)
#define M_SOFTWARE_INT	(0x80000003)
#define S_TIMER_INT		(0x80000005)
#define M_TIMER_INT		(0x80000007)
#define S_EXTERNAL_INT	(0x80000009)
#define M_EXTERNAL_INT	(0x8000000B)

#define M_ACCESS_FAULT_TRAP	(0x00000007)

void trap_handle(uint32_t mcause, uint32_t sp)
{
	switch(mcause & 0x80000FFF)
	{
		case M_SOFTWARE_INT:
		break;
		case M_TIMER_INT:
		break;
		case M_EXTERNAL_INT:
		break;
		case M_ACCESS_FAULT_TRAP:

		break;
		default:
		break;
	}
}

#endif
