#!/bin/bash

# riscv debug
# qemu-system-riscv32 -nographic -machine virt,aclint=on -bios none -kernel dragon_boot.elf -s -S 
# qemu-system-riscv32 -nographic -machine virt,aclint=on -bios dragon_boot.bin -kernel dragon_core.elf -s -S 
# qemu-system-riscv32 -nographic -machine sifive_e -bios none -kernel dragon_boot.elf -s -S 
# qemu-system-riscv32 -nographic -machine sifive_e -bios dragon_boot.bin -kernel dragon_core.elf -s -S 


qemu-system-riscv32 -nographic -machine virt,aclint=on -d guest_errors,cpu_reset -D qemu.log -bios dragon_boot.bin -kernel dragon_core.elf -s -S 


# arm32 debug
# stm32f103 debug
