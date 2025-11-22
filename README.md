## what is dragonRTOS
- dragonRTOS is a configuration operation similar to Linux rtos
## Environmental Construction 
### Install riscv32-unknown-elf- tool chain
### Install qemu-system-riscv32
### Install python3
### Install pip3
### Install kconfiglib
```shell
pip3 install kconfiglib
```
## Build
```shell
source export_env.sh
make menuconfig
make all
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

### debug core app
- open first terminal
```shell
qemu-system-riscv32 -nographic -machine virt -bios dragon_boot.bin -kernel dragon_core.elf -s -S 
```
- open second terminal
```shell
riscv32-unknown-elf-gdb dragon_core.elf
target remote localhost:1234
b app_main
c
```


## Default Memory Map
|        | start address | length   |
| :----: | :-----------: | :----:   |
| boot   | 0x80000000    | 0x2000   |
| kernel | 0x80002000    | 0x2000   |
| app    | 0x80004000    | undefine |
