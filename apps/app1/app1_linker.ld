SECTIONS
{
	. = 0x80004000,
	app_main = .;

	. = ALIGN(8);
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	.data : {*(.data)}

	_app_bss_begin = .;
	.bss : {*(.bss*)}
	_app_bss_end = .;
}
