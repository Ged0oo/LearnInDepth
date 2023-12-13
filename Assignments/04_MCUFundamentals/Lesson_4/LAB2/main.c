#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= 1<<5;
	DDRD |= 1<<6;
	DDRD |= 1<<7;
   
	MCUCR  |= 1;		
	MCUCR  |= 0b11<<2;  
	MCUCSR &= ~(1<<6);  
						
	GICR |= 0b111<<5;	
	sei();				
	
    while (1);
}

ISR(INT0_vect)
{
	GIFR  |= 1<<6; 
	PORTD |= 1<<5; 
	_delay_ms(100); 
	PORTD &= ~(1<<5); 
}

ISR(INT1_vect)
{
	GIFR  |= 1<<7; 
	PORTD |= 1<<6; 
	_delay_ms(100);
	PORTD &= ~(1<<6);
}

ISR(INT2_vect)
{
	GIFR  |= 1<<5; 
	PORTD |= 1<<7; 
	_delay_ms(100);
	PORTD &= ~(1<<7);
}