#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <attributes.h>

#define enable_irq() do{asm volatile ("csrw sie, 1");}while(0);
#define disable_irq() do{asm volatile ("csrw sie, zero");}while(0);

__WEAK void s_software_handle(void);
__WEAK void m_software_handle(void);
__WEAK void s_timer_handle(void);
__WEAK void m_timer_handle(void);
__WEAK void s_exit_handle(void);
__WEAK void m_exit_handle(void);

#endif
