dragon.img: head.o
	$(LD) $^ -T boot_linker.ld -o $@

head.o: head.S
	$(GCC) -c $^
