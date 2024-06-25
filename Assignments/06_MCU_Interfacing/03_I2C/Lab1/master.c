#define F_CPU 8000000UL
#define prescaler	1

#include <avr/io.h>
#include <util/delay.h>

void I2C_init(unsigned long SCL){
	//Set Bit Rate
	TWBR = (unsigned char)((F_CPU/SCL) - 16) / (2 * prescaler);
	//Set TWSP0 and TWPS1
	if(prescaler == 1)
	TWSR = 0;
	else if(prescaler == 4)
	TWSR = 1;
	else if(prescaler == 16)
	TWSR = 2;
	else if(prescaler == 64)
	TWSR = 3;
}

void I2C_start(){
	//Clear TWIE and enable TWI and generate a Start Condition
	TWCR = 1<<TWINT | 1<<TWSTA | 1<<TWEN;
	//Wait to finish
	 while(!(TWCR & 1<<TWINT));
	 //start condition has been transmitted
	 while((TWSR & 0xf8) != 0x08);
}

void I2C_write(unsigned char cByte){
	//write data on TWI data reg
	TWDR = cByte;
	//Clear TWINT
	TWCR = 1<<TWINT | 1<<TWEN;
	//Wait until TWIE is set
	while(!(TWCR & 1<<TWINT));
}

void I2C_stop(){
	TWCR = 1<<TWINT | 1<<TWSTO | 1<<TWEN;
}
	
int main(void)
{
   unsigned char ch = 0;
   I2C_init(0x48);
   
    while (1) 
    {
		_delay_ms(500);
		I2C_start();	//transmit START condition
		I2C_write(0b1101000+0);	//transmit SLA + W(0)
		while((TWSR & 0xf8) != 0x18);	//SLA + W(0) has been transmitted and ACK has been received
		I2C_write(ch++);	//transmit data
		while((TWSR & 0xf8) != 0x28);	//Data has been transmitted and ACK has been received
		I2C_stop(); //transmit STOP condition
    }
}
