#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "SPI_interface.h"

uint16 ch = 'a';

#define SPI_APP_MASTER
//#define SPI_APP_SLAVE

int main(void)
{
	MRCC_voidClockInit(&RCC_obj);
	MRCC_voidPeripheralClockEnable(RCC_APB2_BUS , RCC_GPIOA_CLOCK);
	USART_xInit(USART1, &USART_CnfgSt);
	MCAL_SPI_Init(SPI1, &SPIx_Cnfg);

	while(1)
	{

		#ifdef SPI_APP_MASTER
				ch = USART_u8GetByte(USART1);
				MCAL_SPI_SendData(SPI1, &ch, Enable);
		#endif

		#ifdef SPI_APP_SLAVE
				MCAL_SPI_ReceiveData(SPI1, &ch, Enable);
				USART_vSendByte(USART1, ch);
		#endif

	}
}
