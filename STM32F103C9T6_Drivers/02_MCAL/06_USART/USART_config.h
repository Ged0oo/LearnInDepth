/* 
 * File:   USART_CONFIG.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on February 5, 2024, 8:41 PM
 */

#includes "USART_private"

#ifndef __USART_CONFIG_H__
#define __USART_CONFIG_H__

#define USART_FRACTION_MAX				1550

/* 
 * USART Pins configurations 
 */
#define USART_TX						0
#define USART_RX						1

/* 
 * USART1 configuration 
 */
#define USART1_PORT_TX												GPIOA
#define USART1_PORT_RX												GPIOA
#define USART1_PIN_TX												GPIO_PIN_9
#define USART1_PIN_RX												GPIO_PIN_10

/* 
 * USART2 configuration 
 */
#define USART2_PORT_TX												GPIOB
#define USART2_PORT_RX												GPIOB
#define USART2_PIN_TX												GPIO_PIN_10
#define USART2_PIN_RX												GPIO_PIN_11

/* 
 * USART3 configuration 
 */
#define USART3_PORT_TX												GPIOA
#define USART3_PORT_RX												GPIOA
#define USART3_PIN_TX												GPIO_PIN_2
#define USART3_PIN_RX												GPIO_PIN_3

typedef struct
{
	GPIO_Port_t USART_Port;
	GPIO_Pin_t	USART_Pin;
}USART_MAP_t;

USART_MAP_t USART1_Map[2] = 
{
		{USART1_PORT_TX	,	USART1_PIN_TX},
		{USART1_PORT_RX	,	USART1_PIN_RX}
};

USART_MAP_t USART2_Map[2] = 
{
		{USART2_PORT_TX	,	USART2_PIN_TX},
		{USART2_PORT_RX	,	USART2_PIN_RX}
};

USART_MAP_t USART3_Map[2] = 
{
		{USART3_PORT_TX	,	USART3_PIN_TX},
		{USART3_PORT_RX	,	USART3_PIN_RX}
};


#endif  __USART_CONFIG_H__