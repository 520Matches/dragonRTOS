SECTIONS
{
	. = 0x8022000,
	start_kernel = .;

	. = ALIGN(8);
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	.data : {*(.data)}

	_kernel_bss_begin = .;
	.bss : {*(.bss*)}
	_kernel_bss_end = .;
}
