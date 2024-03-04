/* 
 * File:   USART_PRIVATE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on February 5, 2024, 8:41 PM
 */


#ifndef __USART_PRIVATE_H__
#define __USART_PRIVATE_H__

#include "USART_interface.h"

typedef struct
{
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 BRR;
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 CR3;
	volatile uint32 GTPR;
} USART_t;

#define USART1_BASE_ADDRESS				(0x40013800)
#define USART2_BASE_ADDRESS				(0x40004400)
#define USART3_BASE_ADDRESS				(0x40004800)
	
#define USART1							((USART_t *) USART1_BASE_ADDRESS)
#define USART2							((USART_t *) USART2_BASE_ADDRESS)
#define USART3	     					((USART_t *) USART3_BASE_ADDRESS)
	
/*
 * Bits definition USART_CR1
 */
#define USART_REG_CR1_RE                ((uint16)(1<<2))
#define USART_REG_CR1_TE                ((uint16)(1<<3))
#define USART_REG_CR1_RXNE_EN           ((uint16)(1<<5))
#define USART_REG_CR1_TCIE_EN           ((uint16)(1<<6))
#define USART_REG_CR1_TXE_EN            ((uint16)(1<<7))
#define USART_REG_CR1_PEIE_EN           ((uint16)(1<<8))
#define USART_REG_CR1_UART_WL           ((uint16)(1<<12))
#define USART_REG_CR1_USART_EN          ((uint16)(1<<13))
#define USART_REG_CR1_OVER8             ((uint16)(1<<15))

/*
 * Bits definition USART_CR2
 */
#define USART_REG_CR2_STOP_BITS         12

/*
 * Bit definition for USART_CR3 register
 */
#define UART_STOPBITS_1        			((uint16)0)
#define UART_STOPBITS_HALF     			((uint16)1)
#define UART_STOPBITS_2        			((uint16)2)
#define UART_STOPBITS_ONENHALF 			((uint16)3)
#define USART_REG_CR3_ERR_INT_EN        ((uint16)1)
#define UART_PARITY_NONE                ((uint16)0)
#define UART_HWCONTROL_NONE             ((uint16)0)
#define UART_MODE_TX_RX                 ((uint16)(USART_REG_CR1_TE | USART_REG_CR1_RE))
#define UART_MODE_TX                    ((uint16)(USART_REG_CR1_TE))

/*
 * Error checkers
 */
#define USART_IS_VALID_BAUDRATE(BAUDRATE) 		 (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0044AA21))
#define USART_IS_VALID_STOP_BITS(STOPBITS) 		 (((STOPBITS) == USART_ONE_STOP_BIT) || \
                                     	 	 	 ((STOPBITS) == USART_HALF_STOP_BIT) || \
												 ((STOPBITS) == USART_TWO_STOP_BITS) || \
												 ((STOPBITS) == USART_ONE_AND_HALF_STOP_BIT))
												 
#define USART_IS_VALID_FLOW_CNTRL(CNTRL)		 ((CNTRL == USART_HARDWAREFLOWCONTROL_NONE) 		||\
												 (CNTRL 	== USART_HARDWAREFLOWCONTROL_RTS) 		||\
												 (CNTRL 	== USART_HARDWAREFLOWCONTROL_CTS) 		||\
												 (CNTRL 	== USART_HARDWAREFLOWCONTROL_RTS_CTS))

#define USART_IS_FLAG(FLAG) 					 (((FLAG) == USART_FLAG_PE) || ((FLAG) == USART_FLAG_TXE) || \
												 ((FLAG) == USART_FLAG_TC) || ((FLAG) == USART_FLAG_RXNE) || \
												 ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_LBD) || \
												 ((FLAG) == USART_FLAG_CTS) || ((FLAG) == USART_FLAG_ORE) || \
												 ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE))


#endif  __USART_PRIVATE_H__
