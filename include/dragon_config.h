#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define ARCH 1
#define CROSS_COMPILE "riscv32-unknown-elf-"
#define BOOT_START_ADDR 0x00000000
#define BOOT_LEN 0x1000
#define DTB_ADDR 0x
#define KERNEL_START_ADDR 0x80002000
#define KERNEL_LEN 0x2000
#define KERNEL_STACK_LEN 0x400
#define SIFIVE_E31 1
#define STACK_SIZE 0x400
#define APP_START_ADDR 0x80004000
#define APP_LEN 0x2000
#define APP_MAIN_STACK_LEN 0x400

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CONFIG_H*/
