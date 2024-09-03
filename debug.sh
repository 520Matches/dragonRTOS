#!/bin/bash
# qemu-system-riscv32 -nographic -machine virt -bios none -kernel dragon_boot.elf -s -S 
qemu-system-riscv32 -nographic -machine virt -bios dragon_boot.bin -kernel dragon_core.elf -s -S 
