#include <avr/io.h>

void I2C_init(unsigned char address){
	//Set slave address
	TWAR = address;

}



unsigned char I2C_read(){
	//clear TWINT and enable TWI and ACK
	TWCR = 1<<TWINT | 1<<TWEN | 1<<TWEA;
	//Wait until TWINT is Set
	while(!(TWCR & 1<<TWINT));
	//own SLA + W(0) has been transmitted and ACK has been returned
	while(TWSR != 0x60);
	
	
	TWCR = 1<<TWINT | 1<<TWEN | 1<<TWEA;
	while(!(TWCR & 1<<TWINT));
	//Data has been received and ACK has been returned
	while(TWSR != 0x80);

	//return received data from master
	return TWDR;
}

int main(void)
{
	//make Port A output
	DDRA = 0xff;
	//enable slave at address 1101000 and do not accept general call
	I2C_init(0b1101000);
    while (1) 
    {
		//receive byte
		PORTA = I2C_read();
    }
}

