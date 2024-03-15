SECTION
{
	. = 0x8020000;
	_start = .;

	. = ALIGN(8);
	.text:{*(.text)}
	.rodata:{*(.rodata)}
	.data:{*(.data)}

	_bss_begin = .;
	.bss:{*(.bss*)}
	_bss_end = .;
}
