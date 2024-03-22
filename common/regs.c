#include "regs.h"

void set_reg(volatile uint32_t *addr, uint32_t value)
{
	*addr =  value;
}

uint32_t get_reg(volatile uint32_t *addr)
{
	return *addr;
}
