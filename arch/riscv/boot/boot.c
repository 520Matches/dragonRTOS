#include "../../../include/types.h"

extern uint32_t _bss_begin;
extern uint32_t _bss_end;

void bss_clear(void)
{
	uint32_t *p;
	for(p = &_bss_begin; p < &_bss_end;)
	{
		*p++ = 0;
	}
}

int main(void)
{
	int ret = 0;

	// clear bss
	bss_clear();

	return ret;
}
