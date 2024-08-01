#!/bin/bash
# qemu-system-riscv32 -nographic -machine virt -bios none -kernel dragon_boot.elf -s -S 
# qemu-system-riscv32 -nographic -machine virt -bios dragon_boot.bin -kernel dragon_kernel.elf -s -S 
qemu-system-riscv32 -nographic -machine virt -bios dragon_kernel.bin -kernel dragon_app.elf -s -S 
