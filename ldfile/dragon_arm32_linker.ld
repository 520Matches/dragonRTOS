/* app.ld */
MEMORY {
    FLASH (rx)  : ORIGIN = 0x08004000, LENGTH = 256K - 16K  /* 总Flash 256KB，前16KB给Bootloader */
    RAM (xrw)   : ORIGIN = 0x20000800, LENGTH = 64K - 2K    /* 总RAM 64KB，前2KB给Bootloader */
}

/* 定义APP的栈顶位置 */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS {
    /* APP的中断向量表（需通过VTOR重定位） */
    .isr_vector : {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH

    /* 代码段 */
    .text : {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        . = ALIGN(4);
    } >FLASH

    /* 只读数据段 */
    .rodata : {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    /* 初始化数据段 */
    .data : {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT> FLASH

    /* 未初始化数据段 */
    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM

    /* 动态内存分配 */
    .heap : {
        . = ALIGN(8);
        _heap_start = .;
        . = . + (LENGTH(RAM) - ( _ebss - ORIGIN(RAM) ) - __stack_size); /* 保留1KB栈空间 */
        _heap_end = .;
    } >RAM
}
