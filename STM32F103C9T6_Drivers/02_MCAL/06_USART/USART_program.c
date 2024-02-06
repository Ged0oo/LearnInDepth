/* 
 * File:   USART_PROGRAM.c
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on February 5, 2024, 8:41 PM
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"

USART_InitTypeDef USART_CnfgSt =
{
		.USART_BaudRate = 9600,
		.USART_HWFlowControl = USART_HARDWAREFLOWCONTROL_NONE,
		.USART_Parity = USART_DISABLE_PARITY,
		.USART_TXRX_State = USART_TRANSMITER_RECIEVER,
		.USART_WordLength = USART_EIGHT_BITS,
		.USART_StopBits = USART_ONE_STOP_BIT
};

static void USART_xSetPins(USART_t *USARTx)
{
	GPIO_ConfigType txPIN = {.GPIO_PinMode = GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_PUSHPULL_MODE_2HZ };
	GPIO_ConfigType rxPIN = {.GPIO_PinMode = GPIO_PIN_INPUT_FLOATING_MODE, .GPIO_Logic=GPIO_LOW };

	if(USARTx == USART1)
	{
		txPIN.GPIOx = USART1_Map[USART_TX].USART_Port;
		txPIN.GPIO_PinNumber = USART1_Map[USART_TX].USART_Pin;

		rxPIN.GPIOx = USART1_Map[USART_RX].USART_Port;
		rxPIN.GPIO_PinNumber = USART1_Map[USART_RX].USART_Pin;
	}

	else if(USARTx == USART2)
	{
		txPIN.GPIOx = USART2_Map[USART_TX].USART_Port;
		txPIN.GPIO_PinNumber = USART2_Map[USART_TX].USART_Pin;

		rxPIN.GPIOx = USART2_Map[USART_RX].USART_Port;
		rxPIN.GPIO_PinNumber = USART2_Map[USART_RX].USART_Pin;
	}
	else if(USARTx == USART3)
	{
		txPIN.GPIOx = USART3_Map[USART_TX].USART_Port;
		txPIN.GPIO_PinNumber = USART3_Map[USART_TX].USART_Pin;

		rxPIN.GPIOx = USART3_Map[USART_RX].USART_Port;
		rxPIN.GPIO_PinNumber = USART3_Map[USART_RX].USART_Pin;
	}

	MGPIO_voidInitPortPin(&txPIN);
	MGPIO_voidInitPortPin(&rxPIN);
}
	
static void USART_xConfigBaudRate(USART_t *USARTx, uint32 Copy_u32BaudRate)
{
	uint32 PCLK = 0;

	/*
	 * Get clock frequency of the selected USART clock
	 */
	if(USARTx == USART1)
	{
		PCLK = MRCC_GetPCLK2();
	}
	else
	{
		PCLK = MRCC_GetPCLK1();
	}

	USARTx->BRR = USART_BBR(PCLK, Copy_u32BaudRate);
}

static void USART_xConfigStopBits(USART_t *UARTx, USART_StopBits_t Copy_xNStop)
{	
	/* 
	 * CLEAR 12th and 13 bits 
	 */
	UARTx->CR2 &= ~(0x3 << USART_REG_CR2_STOP_BITS);
	
	/* 
	 * SET 12th and 13 bits
	 */
	UARTx->CR2 |= Copy_xNStop;
}

static void USART_xConfigFlowControl(USART_t *USARTx, USART_FlowCTRL_t Copy_xState)
{
	USARTx->CR3 |= ((Copy_xState & 0x03) << 8);
}

static void USART_xConfigWordLength(USART_t *USARTx, USART_WordLength_t Copy_xLength)
{
	switch(Copy_xLength)
	{
		case USART_NINE_BITS :
			SET_BIT(USARTx->CR1, 12);
			break;
			
		case USART_EIGHT_BITS :
			CLEAR_BIT(USARTx->CR1, 12);
			break;
	}
}

static void USART_xConfigParity(USART_t *USARTx, USART_ParityBIT_t Copy_xParityState)
{
	switch(Copy_xParityState)
	{
		case USART_DISABLE_PARITY :
			CLEAR_BIT(USARTx->CR1, 10);
			break;
		
		case USART_ODD_PARITY :
			SET_BIT(USARTx->CR1, 10);
			SET_BIT(USARTx->CR1, 9);
			break;
		
		case USART_EVEN_PARITY :
			SET_BIT(USARTx->CR1, 10);
			CLEAR_BIT(USARTx->CR1, 9);
			break;
	}
}


void USART_xInit(USART_t *USARTx , USART_InitTypeDef *USART_CnfgSt)
{
	/* 
	 * Configure initial state of the selected USART
	 */
	USART1_CLK_EN();
	SET_BIT(USARTx->CR1, 13);

	/*
	 * Set pins of the selected USART 
	 */
	USART_xSetPins(USARTx);
	
	/* 
	 * Configure word length of the selected USART 
	 */
	USART_xConfigWordLength(USARTx,	USART_CnfgSt->USART_WordLength);
	
	/*
   	 * Configure number of stop bits of the selected USART 
	 */
	USART_xConfigStopBits(USARTx, USART_CnfgSt->USART_StopBits);
	
	/* 
	 * Configure sending mode of the selected USART 
	 */
	USART_xConfigTX_RX(USARTx, USART_CnfgSt->USART_TXRX_State);
	
	/* 
	 * Configure BaudRate of the selected USART 
	 */
	USART_xConfigBaudRate(USARTx, USART_CnfgSt->USART_BaudRate);
	
	/* 
	 * Configure parity state of the selected USART 
	 */
	USART_xConfigParity(USARTx,	USART_CnfgSt->USART_Parity);
	/* 
	 * Configure hardware control flow 
	 */
	USART_xConfigFlowControl(USARTx, USART_CnfgSt->USART_HWFlowControl);
	
	/* 
	 * Configure initial state of the selected USART 
	 */
	SET_BIT(USARTx->CR1, 13);
}

void USART_xConfigTX_RX(USART_t *USARTx, USART_TXRX_t Copy_xState)
{
	/*
	 * Clear TX/RX bits
	 */
	USARTx->CR1 &= ~USART_REG_CR1_RE;
	USARTx->CR1 &= ~USART_REG_CR1_TE;
	
	switch(Copy_xState)
	{
		case USART_TRANSMITER:
			USARTx->CR1 |= USART_REG_CR1_TE;
			break;
	
		case USART_RECIEVER:
			USARTx->CR1 |= USART_REG_CR1_RE;
			break;
	
		case USART_TRANSMITER_RECIEVER:
			USARTx->CR1 |= USART_REG_CR1_RE;
			USARTx->CR1 |= USART_REG_CR1_TE;
			break;
	}
}

void USART_vSendByte(USART_t *USARTx, uint8 data)
{
	/*
	 * Check if TXE bit, Transmit data register empty
	 */
	while(!(USARTx->SR & (1<<7)));

	/*
	 * Put data in the first 8/9 bits of data register
	 */
	USARTx->DR = (uint8)(data & 0xff);
}

uint8 USART_u8GetByte(USART_t *USARTx)
{
	/*
	 * Check if RXNE bit until it is not empty
	 */
	while(!(USARTx->SR & (1<<5)));
	
	/*
	 * Read data register which is not empty
	 */
	uint8 data = (uint8)(USARTx->DR & 0xff);
	return data;
}
