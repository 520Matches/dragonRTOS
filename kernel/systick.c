#include <systick.h>
#include <archs.h>
#include <dragon_types.h>
#include <register.h>

#include <mcu.h>


#define SYS_CLOCK	((uint32_t)(8000000)) //8M
#define SYS_TICK	(1000)	//1ms
							

uint64_t sys_tick = 0;

void systick_init(void)
{
	sys_tick = 0;
	write_csr(mie, 1);

	systick_reload();
}

void systick_reload(void)
{

#if(ARCH == ARCH_RISCV32)
#if(SIFIVE_E31 == 1)
	volatile uint64_t *mtime    = (uint64_t *)(CLINT_BASE + CLINT_MTIME_OFFSET);
	volatile uint64_t *mtimecmp = (uint64_t *)(CLINT_BASE + CLINT_MTIMECMP_OFFSET);
	uint64_t now = *mtime;
	now += (SYS_CLOCK / SYS_TICK);
	*mtimecmp = now;
#endif
#endif

	sys_tick++;
}
