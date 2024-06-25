#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "I2C_interface.h".h"
#include "EEPROM.h"

int main(void)
{
	MRCC_voidClockInit(&RCC_obj);
	MRCC_voidPeripheralClockEnable(RCC_APB2_BUS , RCC_GPIOB_CLOCK);

	uint8 ch1[7] = {1,2,3,4,5,6,7};
	uint8 ch2[7] = {0};

	HAL_EEPROM_Init(I2C1);
	HAL_EEPROM_Receive(I2C1, ch1, 7, 0xaf);
	HAL_EEPROM_Send(I2C1, ch2, 7, 0xaf);

	ch1[0] = 0xa;
	ch1[1] = 0xb;
	ch1[2] = 0xc;
	ch1[3] = 0xd;

	HAL_EEPROM_Receive(I2C1, ch1, 4, 0xfff);
	HAL_EEPROM_Send(I2C1, ch2, 4, 0xfff);

	while(1);
}
