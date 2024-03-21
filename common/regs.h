#ifndef __REG_H
#define __REG_H

void set_reg(volatile uint32_t *addr, uint32_t value);
uint32_t get_reg(volatile uint32_t *addr);

#endif
