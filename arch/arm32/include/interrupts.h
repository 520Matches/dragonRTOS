#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

// 原子操作汇编宏
#define disable_irq()  __asm volatile ("CPSID I")
#define enable_irq()   __asm volatile ("CPSIE I")

#endif
