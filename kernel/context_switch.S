# context_switch.S
.section .text

# 函数: task_switch
# 功能: 任务上下文切换
# 参数: a0 = 当前任务TCB指针, a1 = 下一个任务TCB指针
.global task_switch
task_switch:
    # 保存当前任务上下文
    # 调整sp指针到上下文结构开始处（根据你的TCB结构布局）
    addi sp, sp, -56          # 为14个寄存器分配空间（s0-s11, ra, sp）
    
    # 保存被调用者保存寄存器
    sw ra, 4(sp)             # 保存返回地址
    sw s0, 8(sp)
    sw s1, 12(sp)
    sw s2, 16(sp)
    sw s3, 20(sp)
    sw s4, 24(sp)
    sw s5, 28(sp)
    sw s6, 32(sp)
    sw s7, 36(sp)
    sw s8, 40(sp)
    sw s9, 44(sp)
    sw s10, 48(sp)
    sw s11, 52(sp)
    
    # 保存当前栈指针
    mv t0, sp
    addi t0, t0, 56          # 恢复到调用前的sp
    sw t0, 0(sp)             # 保存sp
    
    # 将上下文保存到当前任务的TCB中
    sw sp, 0(a0)             # 保存上下文指针到current_task->context.sp
    
#ifdef USE_FPU
    # 如果有FPU，保存浮点寄存器上下文
    addi sp, sp, -40
    fsw fs0, 0(sp)
    fsw fs1, 4(sp)
    fsw fs2, 8(sp)
    fsw fs3, 12(sp)
    fsw fs4, 16(sp)
    fsw fs5, 20(sp)
    fsw fs6, 24(sp)
    fsw fs7, 28(sp)
    fsw fs8, 32(sp)
    fsw fs9, 36(sp)
    fsw fs10, 40(sp)
    fsw fs11, 44(sp)
    frcsr t0
    sw t0, 48(sp)
#endif

restore_context:
    # 恢复下一个任务的上下文
    lw sp, 0(a1)             # 从next_task->context.sp加载栈指针
    
#ifdef USE_FPU
    # 恢复浮点寄存器上下文
    flw fs0, 0(sp)
    flw fs1, 4(sp)
    flw fs2, 8(sp)
    flw fs3, 12(sp)
    flw fs4, 16(sp)
    flw fs5, 20(sp)
    flw fs6, 24(sp)
    flw fs7, 28(sp)
    flw fs8, 32(sp)
    flw fs9, 36(sp)
    flw fs10, 40(sp)
    flw fs11, 44(sp)
    lw t0, 48(sp)
    fscsr t0
    addi sp, sp, 52
#endif

    # 恢复被调用者保存寄存器
    lw t0, 0(sp)             # 加载保存的sp值
    lw ra, 4(sp)             # 恢复返回地址
    lw s0, 8(sp)
    lw s1, 12(sp)
    lw s2, 16(sp)
    lw s3, 20(sp)
    lw s4, 24(sp)
    lw s5, 28(sp)
    lw s6, 32(sp)
    lw s7, 36(sp)
    lw s8, 40(sp)
    lw s9, 44(sp)
    lw s10, 48(sp)
    lw s11, 52(sp)
    
    # 恢复栈指针
    mv sp, t0
    
    ret                      # 返回到新任务的ra地址

# 函数: first_task_switch  
# 功能: 第一次任务切换（从内核切换到第一个任务）
# 参数: a0 = 第一个任务的TCB指针
.global first_task_switch
first_task_switch:
    # 直接加载第一个任务的上下文
    lw sp, 0(a0)            # 加载任务的栈指针
    
    # 恢复寄存器（与task_switch中的恢复部分相同）
    lw t0, 0(sp)
    lw ra, 4(sp)
    lw s0, 8(sp)
    lw s1, 12(sp)
    lw s2, 16(sp)
    lw s3, 20(sp)
    lw s4, 24(sp)
    lw s5, 28(sp)
    lw s6, 32(sp)
    lw s7, 36(sp)
    lw s8, 40(sp)
    lw s9, 44(sp)
    lw s10, 48(sp)
    lw s11, 52(sp)
    mv sp, t0
    
    ret
