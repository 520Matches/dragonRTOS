#ifndef __CLINT_H
#define __CLINT_H

#include <archs.h>

#if(ARCH == ARCH_RISCV32)

#define CLINT_BASE	(0x2000000)

#define CLINT_MTIMECMP_OFFSET	(0x4000)
#define CLINT_MTIME_OFFSET	(0xbff8)

#endif


#endif
