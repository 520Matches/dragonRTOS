#!/bin/bash
qemu-system-riscv32 -nographic -machine virt -bios none -kernel dragon_boot.elf -s -S 
