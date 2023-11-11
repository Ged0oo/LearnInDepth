MEMORY
{
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 20K
  FLASH  (rx)     : ORIGIN = 0x8000000,   LENGTH = 64K
}

SECTIONS
{
  .text :
  {
	*(.isr_vector)
    *(.text)           
    *(.text*)  
	. = ALIGN(4);
  } >FLASH

  .data :
  {
    . = ALIGN(4);
    *(.data)           
    *(.data*)          
    . = ALIGN(4);
  } >RAM AT> FLASH

  .bss :
  {
	. = ALIGN(4);
    *(.bss)            
    *(.bss*)           
    . = ALIGN(4);
  } >RAM
    
  . = . + 0x1000;
  Stack_Top = .;
}