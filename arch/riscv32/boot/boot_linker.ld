SECTIONS
{
	. = 0x8020000,
	_start = .;

	. = ALIGN(8);
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	.data : {*(.data)}

	_boot_bss_begin = .;
	.bss : {*(.bss*)}
	_boot_bss_end = .;
}
