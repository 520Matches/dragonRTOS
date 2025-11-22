#include <spinlock.h>

// 中断状态保存实现
uint32_t get_primask(void) {
    uint32_t result;
    __asm volatile ("MRS %0, PRIMASK" : "=r" (result));
    return result;
}

void set_primask(uint32_t priMask) {
    __asm volatile ("MSR PRIMASK, %0" : : "r" (priMask));
}

// 自旋锁获取（使用LDREX/STREX实现）
void spin_lock(spinlock_t *lock) {
    uint32_t tmp;
    __asm volatile (
        "1: LDREX %0, [%1]\n"   // 加载独占状态
        "   CMP %0, #0\n"       // 检查锁状态
        "   ITT NE\n"          
        "   STREXNE %0, %2, [%1]\n" // 尝试获取锁
        "   CMPNE %0, #0\n"
        "   BNE 1b\n"           // 循环直到获取锁
        "   DMB\n"             // 数据内存屏障
        : "=&r" (tmp)
        : "r" (lock), "r" (1)
        : "memory"
    );
}

// 自旋锁释放
void spin_unlock(spinlock_t *lock) {
    __asm volatile (
        "DMB\n"               // 保证所有内存访问完成
        "STR %1, [%0]\n"       // 释放锁
        : 
        : "r" (lock), "r" (0)
        : "memory"
    );
}

