#!/bin/bash
qemu-system-riscv32 -nographic -M virt -bios none -kernel dragon.bin
