#ifndef __IRQ_H
#define __IRQ_H

#include <archs.h>

#if(ARCH == ARCH_RISCV32)
	#include "../arch/riscv32/include/interrupts.h"
#endif

#endif
