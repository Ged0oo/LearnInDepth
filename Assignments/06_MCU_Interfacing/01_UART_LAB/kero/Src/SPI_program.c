/* 
 * File:   SPI_PROGRAM.c
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on Febreuary 16, 2024, 8:41 PM
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"


SPI_Config_t SPIx_Cnfg =
{
		.BRPrescaller = SPI_CONFIGURED_BR_PRESCALER,
		.ClockPhase = SPI_CONFIGURED_ClockPhase,
		.ClockPolarity = SPI_CONFIGURED_ClockPolarity,
		.CommunicationMode = SPI_CONFIGURED_MODE,
		.DataSize = SPI_CONFIGURED_DataSize,
		.FrameFormat = SPI_CONFIGURED_FrameFormat,
		.Mode = SPI_CONFIGURED_MODE,
		.NSS = SPI_CONFIGURED_NSS,
		.IRQEnable = SPI_CONFIGURED_IRQ_ENABLE,
		.IRQ_CallBack = SPI_CONFIGURED_IRQ_CALLBACK
};


void MCAL_SPI_Init(SPI_t* SPIx, SPI_Config_t* SPI_Config)
{
	/*
	 * Enable Clock
	 */
	if(SPIx == SPI1)
		SPI1_CLK_EN();
	else if (SPIx == SPI2)
		SPI2_CLK_EN();

	/*
	 * Master / Slave Mode Selection
	 */
	SPIx->CR1 |= SPI_Config->Mode;

	/*
	 * Communication Mode Selection
	 */
	SPIx->CR1 |= SPI_Config->CommunicationMode;

	/*
	 * Frame Format Selection
	 */
	SPIx->CR1 |= SPI_Config->FrameFormat;

	/*
	 * Data Size Selection
	 */
	SPIx->CR1 |= SPI_Config->DataSize;

	/*
	 * Baud Rate Prescaler
	 */
	SPIx->CR1 |= SPI_Config->BRPrescaller;

	/*
	 * Clock Polarity Selection
	 */
	SPIx->CR1 |= SPI_Config->ClockPolarity;

	/*
	 * Clock Phase Selection
	 */
	SPIx->CR1 |= SPI_Config->ClockPhase;

	/*
	 * NSS Configuration
	 */
	if((SPI_Config->NSS == SPI_NSS_SW_SLAVE) || (SPI_Config->NSS == SPI_NSS_SW_MASTER))
		SPIx->CR1 |= SPI_Config->NSS;
	else
		SPIx->CR2 |= SPI_Config->NSS;

	/*
	 * Setting IRQs Configuration
	 */
	if(SPI_Config->IRQEnable != SPI_IRQ_Enable_None)
	{
		SPIx->CR2 |= SPI_Config->IRQEnable;
		if(SPIx == SPI1)
			NVIC_IRQ35_SPI1_Enable();
		else if (SPIx == SPI2)
			NVIC_IRQ36_SPI2_Enable();
	}

	/*
	 * Configure SPI Pins
	 */
	MCAL_SPI_ConigurePins(SPIx, SPI_Config);
	MCAL_SPI_ConigureSlavePins(SPIx, SPI_Config);

	/*
	 * Enable SPI Module
	 */
	SPIx->CR1 |= SPI_ENABLE;
}


void MCAL_SPI_DeInit(SPI_t* SPIx)
{
	if(SPIx == SPI1)
	{
		RCC->APB2RSTR |= 1<<12;
		NVIC_IRQ35_SPI1_Disable();
	}

	else if(SPIx == SPI2)
	{
		RCC->APB1RSTR |= 1<<14;
		NVIC_IRQ36_SPI2_Disable();
	}

}


void MCAL_SPI_SendData(SPI_t* SPIx, uint16* p_Txbuffer, Polling_e Polling)
{
	if(Polling == Enable)
		while(!(SPIx->SR & 1<<1));
	SPIx->DR = *p_Txbuffer;
}


void MCAL_SPI_ReceiveData(SPI_t* SPIx, uint16* p_Rxbuffer, Polling_e Polling)
{
	if(Polling == Enable)
		while(!(SPIx->SR & 1));
	*p_Rxbuffer = SPIx->DR ;
}


void MCAL_SPI_TX_RX(SPI_t* SPIx, uint16* p_buffer, Polling_e Polling)
{
	if(Polling == Enable)
	{
		while(!(SPIx->SR & 1<<1));
	}
	SPIx->DR = *p_buffer;

	if(Polling == Enable)
	{
		while(!(SPIx->SR & 1));
	}
	*p_buffer = SPIx->DR ;
}


IRQSource_t irq_src;


void MCAL_SPI_ConigureSlavePins(SPI_t* SPIx, SPI_Config_t *SPIx_Cnfg)
{
	uint8 Local_u8Index	= 0;

	/*
	 * Initialize slave pins as output and make their ideal state is high
	 */
	if(SPI_MASTER_MODE	==	SPIx_Cnfg->Mode)
	{
		if(SPI_NSS_HW_MASTER_OUT	==	SPIx_Cnfg->NSS)
		{
			GPIO_ConfigType xpin =
			{
					.GPIOx = SPI_MapCnfg[Local_u8Index].SlavePort,
					.GPIO_PinNumber = SPI_MapCnfg[Local_u8Index].SlavePin,
					.GPIO_PinMode = GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_PUSHPULL_MODE_2HZ,
					.GPIO_Logic = GPIO_HIGH
			};
			MGPIO_voidInitPortPin(&xpin);
		}

		else if(SPI_NSS_HW_MASTER_IN	==	SPIx_Cnfg->NSS)
		{
			GPIO_ConfigType xpin =
			{
					.GPIOx = SPI_MapCnfg[Local_u8Index].SlavePort,
					.GPIO_PinNumber = SPI_MapCnfg[Local_u8Index].SlavePin,
					.GPIO_PinMode = GPIO_PIN_INPUT_FLOATING_MODE
			};
			MGPIO_voidInitPortPin(&xpin);
		}
	}
	else if(SPI_SLAVE_MODE	==	SPIx_Cnfg->Mode)
	{
		if(SPI_NSS_HW_SLAVE	==	SPIx_Cnfg->NSS)
		{
			GPIO_ConfigType xpin =
			{
					.GPIOx = SPI_MapCnfg[Local_u8Index].SlavePort,
					.GPIO_PinNumber = SPI_MapCnfg[Local_u8Index].SlavePin,
					.GPIO_PinMode = GPIO_PIN_INPUT_FLOATING_MODE
			};
			MGPIO_voidInitPortPin(&xpin);
		}
	}
}


void MCAL_SPI_ConigurePins(SPI_t* SPIx, SPI_Config_t *SPIx_Cnfg)
{
	uint8 Local_u8Index	= 0;

	GPIO_ConfigType miso =
	{
			.GPIOx = SPI_MISO_PORT,
			.GPIO_PinNumber = SPI_MISO_PIN,
			.GPIO_PinMode = GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_PUSHPULL_MODE_10MHZ
	};

	GPIO_ConfigType mosi =
	{
			.GPIOx = SPI_MOSI_PORT,
			.GPIO_PinNumber = SPI_MOSI_PIN,
			.GPIO_PinMode = GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_PUSHPULL_MODE_10MHZ
	};

	GPIO_ConfigType clk =
	{
			.GPIOx = SPI_CLK_PORT,
			.GPIO_PinNumber = SPI_MapCnfg[Local_u8Index].SlavePin,
			.GPIO_PinMode = GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_PUSHPULL_MODE_10MHZ
	};

	MGPIO_voidInitPortPin(&miso);
	MGPIO_voidInitPortPin(&mosi);
	MGPIO_voidInitPortPin(&clk);
}


void SPI1_IRQHandler()
{
	IRQSource_t irq_src;
	irq_src.TXE = (SPI1->SR >> 1)&1;
	irq_src.RXE = (SPI1->SR )&1;
	irq_src.ERRI = ((SPI1->SR >> 4)&1) | ((SPI1->SR >> 5)&1) | ((SPI1->SR >> 6)&1);
	SPIx_Cnfg.IRQ_CallBack(irq_src);
}


void SPI2_IRQHandler()
{
	IRQSource_t irq_src;
	irq_src.TXE = (SPI2->SR >> 1)&1;
	irq_src.RXE = (SPI2->SR )&1;
	irq_src.ERRI = ((SPI2->SR >> 4)&1) | ((SPI2->SR >> 5)&1) | ((SPI2->SR >> 6)&1);
	SPIx_Cnfg.IRQ_CallBack(irq_src);
}
