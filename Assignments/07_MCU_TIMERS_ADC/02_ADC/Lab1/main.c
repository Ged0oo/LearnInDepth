#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	//Make PORTD output 
    DDRD = 0xff;
	//Make PC0 PC1 output
	DDRC = 0b11;
	
	//Make internal 2.56V Vref 
	ADMUX |= 1<<REFS1 | 1<<REFS0;
	//Set Pre-Scaler to CLK/128
	ADCSRA |= 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;
	//Enable Global Interrupt
	sei();
	//Enable ADC Interrupt
	ADCSRA |= 1<<ADIE;
	//Enable ADC
	ADCSRA |= 1<<ADEN;
	//Start Conversion
	ADCSRA |= 1<<ADSC;
    while (1) 
    {
    }
}

ISR(ADC_vect){
	//Read Converted Signal
	PORTD = ADCL;
	PORTC = ADCH; 
	
	//Start Conversion
	ADCSRA |= 1<<ADSC;
}

