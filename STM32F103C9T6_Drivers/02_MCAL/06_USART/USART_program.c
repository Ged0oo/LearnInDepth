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

static void USART_xSetPins(USART_t *USARTx)
{
	switch(USARTx)
	{
		case USART1 :
			GPIO_vInitPortPin(	USART1_Map[USART_TX].USART_Port,
								USART1_Map[USART_TX].USART_Pin,
								GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_2MHZ);
								
			GPIO_vInitPortPin(	USART1_Map[USART_RX].USART_Port,
								USART1_Map[USART_RX].USART_Pin,
								GPIO_PIN_INPUT_FLOATING_MODE);
			break;
		
		case USART2 :
			GPIO_vInitPortPin(	USART2_Map[USART_TX].USART_Port,
								USART2_Map[USART_TX].USART_Pin,
								GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_2MHZ);
								
			GPIO_vInitPortPin(	USART2_Map[USART_RX].USART_Port,
								USART2_Map[USART_RX].USART_Pin,
								GPIO_PIN_INPUT_FLOATING_MODE);
			break;
			
		case USART3 :
			GPIO_vInitPortPin(	USART3_Map[USART_TX].USART_Port,
								USART3_Map[USART_TX].USART_Pin,
								GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_2MHZ);
								
			GPIO_vInitPortPin(	USART3_Map[USART_RX].USART_Port,
								USART3_Map[USART_RX].USART_Pin,
								GPIO_PIN_INPUT_FLOATING_MODE);
			break;
	}
}
	
static void USART_xConfigBaudRate(USART_t *USARTx, uint32 Copy_u32BaudRate)
{
	
}

static void USART_xConfigStopBits(USART_t *UARTx, USART_StopBits_t Copy_xNStop)
{	
	/* 
	 * CLEAR 12th and 13 bits 
	 */
	UARTx->CR2 &= ~( 0x3 << USART_REG_CR2_STOP_BITS);
	
	/* 
	 * SET 12th and 13 bits
	 */
	UARTx->CR2 |= Copy_xNStop;
}

static void USART_xConfigFlowControl(USART_t *USARTx, USART_FlowCTRL_t Copy_xState)
{
	USARTx->CR3 |= ((Copy_xState & 0x0300) << 8);
}

static void USART_xConfigWordLength(USART_t *USARTx, USART_WordLength_t Copy_xLength)
{
	switch(Copy_xLength)
	{
		case USART_NINE_BITS :
			USARTx->CR1 |= USART_REG_CR1_UART_WL;
			break;
			
		case USART_NINE_BITS :
			USARTx->CR1 &= ~USART_REG_CR1_UART_WL;
			break;
	}
}

static void USART_xConfigParity(USART_t *USARTx, USART_ParityBit_t Copy_xParityState)
{
	switch(Copy_xLength)
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

void USART_xInitStruct(USART_InitTypeDef *USART_CnfgSt)
{
	if(USART_CnfgSt == NULL)
		return;

	USART_CnfgSt->USART_BaudRate				=	9600;
	USART_CnfgSt->USART_HardwareFlowControl		=	DISABLE;
	USART_CnfgSt->USART_Parity					=	DISABLE;
	USART_CnfgSt->USART_TXRX_State				=	USART_TRANSMITER_RECIEVER;
	USART_CnfgSt->USART_WordLength				=	USART_EIGHT_BITS;
	USART_CnfgSt->USART_StopBits				=	USART_ONE_STOP_BIT;
	USART_CnfgSt->USART_InitialState			=	ENABLE;
}

void USART_xInit(USART_t *USARTx , USART_InitTypeDef *USART_CnfgSt)
{
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
	USART_xConfigFlowControl(USARTx, USART_CnfgSt->USART_HardwareFlowControl);
	
	/* 
	 * Configure initial state of the selected USART 
	 */
	USART_xConfigState(USARTx, USART_CnfgSt->USART_InitialState);
}

void USART_xConfigTX_RX(USART_t *USARTx,USART_TXRX_t Copy_xState)
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

void USART_xConfigState(USART_t *USARTx , FunctionalState Copy_xState)
{
	switch(Copy_xState)
	{
		case DISABLE:
			CLEAR_BIT(USARTx->CR1, 13);
			break;
			
		case ENABLE:
			SET_BIT(USARTx->CR1, 13);
			break;
	}
}

void USART_vSendByte(USART_t *USARTx,uint8 data)
{
	/*
	* Put data in the first 8 bits of data register
	*/
	USARTx->DR = data;

	/*
	 * Check if TXE bit, Transmit data register empty
	 */
	while(!(USARTx->SR & (1<<7)));
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
	uint8 data = USARTx->DR & 0xFF;
	return data;
}
