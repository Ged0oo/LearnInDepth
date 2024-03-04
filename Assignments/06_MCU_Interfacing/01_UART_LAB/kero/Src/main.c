#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "SPI_interface.h"

uint16 ch = 'a';

int main(void)
{
	MRCC_voidClockInit(&RCC_obj);
	MRCC_voidPeripheralClockEnable(RCC_APB2_BUS , RCC_GPIOA_CLOCK);
	USART_xInit(USART1, &USART_CnfgSt);

	while(1)
	{
		ch = USART_u8GetByte(USART1);
		USART_vSendByte(USART1, ch);
	}
}
