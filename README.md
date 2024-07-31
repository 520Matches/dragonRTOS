## what is dragonRTOS
- dragonRTOS is a configuration operation similar to Linux rtos
## Environmental Construction 
### Install python3
### Install pip3
### Install kconfiglib
```shell
pip3 install kconfiglib
```
## Build
```shell
make menuconfig
make -j$(nproc)
```

## Debug
- use qemu to debug
### debug boot
- open first terminal
```shell
qemu-system-riscv32 -nographic -machine virt -bios none -kernel dragon_boot.elf -s -S 
```
- open second terminal
```shell
riscv32-unknown-elf-gdb dragon_boot.elf
target remote localhost:1234
b _start
c
```

### debug kernel
- open first terminal
```shell
qemu-system-riscv32 -nographic -machine virt -bios dragon_boot.bin -kernel dragon_kernel.elf -s -S 
```
- open second terminal
```shell
riscv32-unknown-elf-gdb dragon_kernel.elf
target remote localhost:1234
b _start
c
```

### debug app


## Default Memory Map
|        | start address | length   |
| boot   | 0x80000000    | 0x2000   |
| kernel | 0x80002000    | 0x2000   |
| app    | 0x80004000    | undefine |
