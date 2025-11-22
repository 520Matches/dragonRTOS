#ifndef __SPINLOCK_H
#define __SPINLOCK_H

#include <stdint.h>

typedef volatile uint32_t spinlock_t;

uint32_t get_primask(void);

void set_primask(uint32_t priMask);

// 自旋锁获取（使用LDREX/STREX实现）
void spin_lock(spinlock_t *lock);

// 自旋锁释放
void spin_unlock(spinlock_t *lock);

#endif
