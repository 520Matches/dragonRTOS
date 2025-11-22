#ifndef __TASK_H
#define __TASK_H

#include <stdint.h>

// 任务上下文结构体（需要与汇编中的保存顺序匹配）
typedef struct {
    // 被调用者保存寄存器
    uint32_t sp;        // 栈指针
    uint32_t ra;        // 返回地址
    uint32_t s0;        // 被调用者保存寄存器
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t s8;
    uint32_t s9;
    uint32_t s10;
    uint32_t s11;
    
    // 浮点寄存器上下文（如果有FPU）
    #ifdef USE_FPU
    uint32_t fcsr;
    uint32_t fs0, fs1, fs2, fs3, fs4, fs5, fs6, fs7;
    uint32_t fs8, fs9, fs10, fs11;
    #endif
} task_context_t;

// 任务控制块
typedef struct task_control_block {
    task_context_t context;     // 任务上下文
    uint32_t *stack_base;       // 栈底地址
    uint32_t stack_size;        // 栈大小
    uint32_t priority;          // 优先级
    struct task_control_block *next; // 就绪队列指针
    uint32_t state;             // 任务状态
    char name[16];              // 任务名
} tcb_t;

// 任务状态定义
#define TASK_READY      0
#define TASK_RUNNING    1
#define TASK_BLOCKED    2
#define TASK_SUSPENDED  3

// 全局变量声明
extern tcb_t *current_task;
extern tcb_t *next_task;

#endif
