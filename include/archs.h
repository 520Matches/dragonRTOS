#ifndef __ARCHS_H
#define __ARCHS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <dragon_config.h>

#define ARCH_RISCV32	1
#define ARCH_RISCV64	2
#define ARCH_ARM32		3
#define ARCH_ARM64		4

#if(ARCH == ARCH_RISCV32)
	#define POINT_LEN	(1 << 2)
#else
	#define POINT_LEN	(1 << 2)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
