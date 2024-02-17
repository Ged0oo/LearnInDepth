/* 
 * File:   USART_CONFIG.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on February 5, 2024, 8:41 PM
 */



#ifndef __USART_CONFIG_H__
#define __USART_CONFIG_H__

#include "GPIO_interface.h"

#define USART_FRACTION_MAX				1550

#define USART_CONFUGURED_BR				9600
#define USART_CONFUGURED_HW_FLOW		USART_HARDWAREFLOWCONTROL_NONE
#define USART_CONFUGURED_Parity			USART_DISABLE_PARITY
#define USART_CONFUGURED_TXRX_STATE		USART_TRANSMITER_RECIEVER
#define USART_CONFUGURED_WORD_LENGTH	USART_EIGHT_BITS
#define USART_CONFUGURED_STOP_BITS		USART_ONE_STOP_BIT

/* 
 * USART Pins configurations 
 */
#define USART_TX						0
#define USART_RX						1

/* 
 * USART1 configuration 
 */
#define USART1_PORT												    GPIOA
#define USART1_PIN_TX												GPIO_PIN_9
#define USART1_PIN_RX												GPIO_PIN_10

/* 
 * USART2 configuration 
 */
#define USART2_PORT													GPIOA
#define USART2_PIN_TX												GPIO_PIN_2
#define USART2_PIN_RX												GPIO_PIN_3

/* 
 * USART3 configuration 
 */
#define USART3_PORT													GPIOB
#define USART3_PIN_TX												GPIO_PIN_10
#define USART3_PIN_RX												GPIO_PIN_11

typedef struct
{
	GPIO_t * USART_Port;
	GPIO_t *	USART_Pin;
}USART_MAP_t;

USART_MAP_t USART1_Map[2] = 
{
		{USART1_PORT	,	USART1_PIN_TX},
		{USART1_PORT	,	USART1_PIN_RX}
};

USART_MAP_t USART2_Map[2] = 
{
		{USART2_PORT	,	USART2_PIN_TX},
		{USART2_PORT	,	USART2_PIN_RX}
};

USART_MAP_t USART3_Map[2] = 
{
		{USART3_PORT	,	USART3_PIN_TX},
		{USART3_PORT	,	USART3_PIN_RX}
};


#endif  __USART_CONFIG_H__
