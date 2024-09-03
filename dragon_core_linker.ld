SECTIONS
{
	. = 0x80002000,
	start_kernel = .;
	.text ALIGN(4): {
		*(.text)
	}
	.rodata : {*(.rodata)}
	.data : {*(.data)}

	_core_bss_begin = .;
	.bss : {*(.bss*)}
	_core_bss_end = .;
}
