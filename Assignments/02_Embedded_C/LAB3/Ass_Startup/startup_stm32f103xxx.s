// Mohamed Nagy
// startup_stm32f103xxx.s

.section .isr_vector
.word Stack_Top
.word _Reset_Handler
.word _Default_Handler

.section .text
_Reset_Handler:
	bl main
	b .
	
.thumb_func
_Default_Handler:
	b _Reset_Handler
	