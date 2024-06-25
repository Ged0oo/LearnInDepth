#include <avr/io.h>

void I2C_init(unsigned char address){
	//Set slave address
	TWAR = address;
}

void I2C_read(){
	//clear TWINT and enable TWI and ACK
	TWCR = 1<<TWINT | 1<<TWEN | 1<<TWEA;
	//Wait until TWINT is Set
	while(!(TWCR & 1<<TWINT));
	//own SLA + R(1) has been received and ACK has been returned
	while(TWSR != 0xa8);
}

void I2C_write(unsigned char data){
	TWDR = data;
	TWCR = 1<<TWINT | 1<<TWEN;
	while(!(TWCR & 1<<TWINT));
}

int main(void)
{
	unsigned char data = 0;
	//enable slave at address 1101000 and do not accept general call
	I2C_init(0b1101000);
	
    while (1) 
    {
		 I2C_read();
		 I2C_write(data++);
    }
}
