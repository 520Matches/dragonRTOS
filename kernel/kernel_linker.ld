SECTIONS
{
	. = 0x80002000,
	start_kernel = .;

	. = ALIGN(8);
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	.data : {*(.data)}

	_kernel_bss_begin = .;
	.bss : {*(.bss*)}
	_kernel_bss_end = .;
}
