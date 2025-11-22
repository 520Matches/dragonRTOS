/******************************************************************
* 汇编启动代码 (head.s)
* 功能：
*   1. 定义中断向量表
*   2. 初始化堆栈指针
*   3. 初始化 .data 和 .bss 段
*   4. 跳转到 C 主程序
******************************************************************/

.syntax unified
.cpu cortex-m3
.thumb

// 内存布局定义（根据实际芯片调整）
.equ  STACK_SIZE, 0x00000400  // 1KB 堆栈
.equ  START_KERNEL,  0x08004000   // C 程序起始地址

// 中断向量表定义
.section .isr_vector
.global __vectors
__vectors:
    .word _estack              // 栈顶地址
    .word reset_handler        // 复位处理程序
    .word nmi_handler          // NMI 处理程序
    .word hardfault_handler    // HardFault 处理程序
    // ... 其他中断向量（根据需求添加）
    .word 0                    // 结束标记

// 默认中断处理（无限循环）
.thumb_func
# .weak reset_handler
# reset_handler:
#     b .
#
.thumb_func
.weak nmi_handler
nmi_handler:
    b .

.thumb_func
.weak hardfault_handler
hardfault_handler:
    b .

// 堆栈分配
.section .stack
// 8字节对齐 2^3
.align 3
.global _stack
_stack:
    .space STACK_SIZE
.set _estack, . + STACK_SIZE  // 栈顶地址

// 数据段初始化
.section .text.reset_handler
.global reset_handler
.thumb_func
reset_handler:
    // 1. 初始化堆栈指针
    ldr r0, =_estack
    mov sp, r0

    // 2. 复制 .data 段到 RAM
    ldr r0, =_sidata  // ROM 中的 .data 起始地址
    ldr r1, =_sdata   // RAM 中的 .data 起始地址
    ldr r2, =_edata
    subs r2, r2, r1
    ble copy_data_done

copy_data_loop:
    ldrb r3, [r0], #1
    strb r3, [r1], #1
    subs r2, #1
    bne copy_data_loop

copy_data_done:

    // 3. 清零 .bss 段
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
    subs r1, r1, r0
    ble zero_bss_done

zero_bss_loop:
    strb r2, [r0], #1
    subs r1, #1
    bne zero_bss_loop

zero_bss_done:

    // 4. 初始化系统时钟（可选）
    // bl SystemInit

    // 5. 跳转到 C 主程序
    ldr r0, =boot_main
    bx r0

// 保持处理器运行
loopforever:
    b loopforever

// 链接脚本需要的符号定义
.global _sidata
_sidata: .word _sidata
.global _sdata
_sdata: .word _sdata
.global _edata
_edata: .word _edata
.global _sbss
_sbss: .word _sbss
.global _ebss
_ebss: .word _ebss
