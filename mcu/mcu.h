
#ifndef __MCU_H
#define __MCU_H

#include <dragon_config.h>
#include <archs.h>

#if(ARCH == ARCH_RISCV32)
	#include "./riscv32/clint.h"
#endif

#endif
