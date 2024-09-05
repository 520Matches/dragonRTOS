
#ifndef __MCU_H
#define __MCU_H

#include <dragon_config.h>
#include <archs.h>

#if(ARCH == ARCH_RISCV32)
#if(SIFIVE_E31 == 1)
	#include "./riscv32/sifive_e31/clint.h"
#endif
#endif

#endif
