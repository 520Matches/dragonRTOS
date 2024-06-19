SECTIONS
{
	. = 0x80000000,
	_start = .;

	. = ALIGN(8);
	.text.boot : {*(.text.boot)}
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	.data : {*(.data)}

	_boot_bss_begin = .;
	.bss : {*(.bss*)}
	_boot_bss_end = .;
}
