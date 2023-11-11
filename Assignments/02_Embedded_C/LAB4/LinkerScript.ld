MEMORY
{
	FLASH (RX)  : ORIGIN = 0x00000000, LENGTH = 512M
	RAM  (RWX) : ORIGIN = 0X20000000, LENGTH = 512M
}

SECTIONS
{
	.text :
	{
		. = ALIGN(4);
		*(.vectors*)
		*(.text)
	    *(.text*)
		*(.rodata)
		. = ALIGN(4);
		_E_text = .;
	}>FLASH	
	
	.data :
	{
		. = ALIGN(4);
	    _S_DATA = .;
		*(.data)
		. = ALIGN(4);
	    _E_DATA = .;
	}>RAM AT>FLASH

	.bss :
	{
		. = ALIGN(4);
	    _S_bss = .;
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
		 _E_bss = .;
	}>RAM	
}