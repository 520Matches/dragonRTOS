SECTIONS
{
	. = 0x8022000,
	start_kernel = .;

	. = ALIGN(8);
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	.data : {*(.data)}

	_bss_begin = .;
	.bss : {*(.bss*)}
	_bss_end = .;
}
