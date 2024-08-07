/* 
 * File:   USART_INTERFACE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on February 5, 2024, 8:41 PM
 */


#ifndef __USART_INTERFACE_H__
#define __USART_INTERFACE_H__

#include "USART_private.h"

#define USART1_CLK_EN()  (RCC->APB2ENR |= 1<<14)

/*
 * Stop Bits
 */
#define USART_ONE_STOP_BIT              ((uint32) 0<<12 )
#define USART_HALF_STOP_BIT             ((uint32) 1<<12 )
#define USART_TWO_STOP_BITS             ((uint32) 2<<12 )
#define USART_ONE_AND_HALF_STOP_BIT     ((uint32) 3<<12 )
typedef unsigned int					USART_StopBits_t;

/*
 * Baud rate Calculations
 */
#define USARTDIV(_PCLK_,_BAUD_)			  (uint32)(_PCLK_ / (16 * _BAUD_))
#define USARTDIV_MUL100(_PCLK_,_BAUD_)	  (uint32)(25 * _PCLK_ / (4 * _BAUD_))
#define Mantissa(_PCLK_,_BAUD_)			  USARTDIV(_PCLK_,_BAUD_)
#define Mantissa_MUL100(_PCLK_,_BAUD_)	  USARTDIV(_PCLK_,_BAUD_) * 100
#define	DIV_Fraction(_PCLK_,_BAUD_)		  ((USARTDIV_MUL100(_PCLK_,_BAUD_) - Mantissa_MUL100(_PCLK_,_BAUD_)) * 16) / 100
#define USART_BBR(_PCLK_,_BAUD_)		  (Mantissa(_PCLK_,_BAUD_) << 4) | (DIV_Fraction(_PCLK_,_BAUD_) & 0xf)

/*
 * Flags definitions
 */
#define USART_FLAG_CTS                   ((uint16)0x0200)
#define USART_FLAG_LBD                   ((uint16)0x0100)
#define USART_FLAG_TXE                   ((uint16)0x0080)
#define USART_FLAG_TC                    ((uint16)0x0040)
#define USART_FLAG_RXNE                  ((uint16)0x0020)
#define USART_FLAG_IDLE                  ((uint16)0x0010)
#define USART_FLAG_ORE                   ((uint16)0x0008)
#define USART_FLAG_NE                    ((uint16)0x0004)
#define USART_FLAG_FE                    ((uint16)0x0002)
#define USART_FLAG_PE                    ((uint16)0x0001)

/* 
 * USART interrupts data type 
 */
typedef enum
{
	USART_INTERRUPT_OFF,
	USART_INTERRUPT_ON,
	USART_INTERRUPT_RX_ON,
	USART_INTERRUPT_RX_OFF,
	USART_INTERRUPT_TX_ON,
	USART_INTERRUPT_TX_OFF,
	USART_INTERRUPT_PE_ON,
	USART_INTERRUPT_PE_OFF,
	USART_INTERRUPT_IDLE_ON,
	USART_INTERRUPT_IDLE_OFF,
	USART_INTERRUPT_TC_ON,
	USART_INTERRUPT_TC_OFF,
	USART_INTERRUPT_ERR_OFF,
	USART_INTERRUPT_ERR_ON
}USART_INT_t;

/* 
 * USART modes data type 
 */
typedef enum
{
	USART_TRANSMITER,
	USART_RECIEVER,
	USART_TRANSMITER_RECIEVER
}USART_TXRX_t;

/* 
 * USART word length data type
 */
typedef enum
{
	USART_EIGHT_BITS,
	USART_NINE_BITS
}USART_WordLength_t;

/* 
 * USART parity data type
 */
typedef enum
{
	USART_DISABLE_PARITY,
	USART_EVEN_PARITY,
	USART_ODD_PARITY
}USART_ParityBIT_t;

/* 
 * USART hardware control flow data type 
 */
typedef enum
{
	USART_HARDWAREFLOWCONTROL_NONE,
	USART_HARDWAREFLOWCONTROL_RTS ,
	USART_HARDWAREFLOWCONTROL_CTS,
	USART_HARDWAREFLOWCONTROL_RTS_CTS
}USART_FlowCTRL_t;

/* 
 * Clock data structure for future use
 */
typedef struct
{
	uint16 USART_Clock;   /*  Specifies whether the USART clock is enabled or disabled. */
	uint16 USART_CPOL;    /*  Specifies the steady state value of the serial clock. */
	uint16 USART_CPHA;    /*  Specifies the clock transition on which the bit capture is made. */
	uint16 USART_LastBit; /*  Specifies whether the clock pulse corresponding to the last transmitted
                               data bit (MSB) has to be output on the SCLK pin in synchronous mode. */
} USART_ClockInitTypeDef;

/* USART Configuration structure */
typedef struct
{
	uint32 USART_BaudRate;            		/* 	This member configures the USART communication baud rate.
												The baud rate is computed using the following formula:
											  - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
											  - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

	USART_WordLength_t USART_WordLength;	/* Specifies the number of data bits transmitted or received in a frame. */

	USART_StopBits_t USART_StopBits;  		/* Specifies the number of stop bits transmitted. */

	USART_ParityBIT_t USART_Parity;         /* 	Specifies the parity mode.
												When parity is enabled, the computed parity is inserted
												at the MSB position of the transmitted data (9th bit when
												the word length is set to 9 data bits; 8th bit when the
												word length is set to 8 data bits). */

	USART_FlowCTRL_t USART_HWFlowControl; 	/* 	Specifies wether the hardware flow control mode is enabled
												or disabled. */

	USART_TXRX_t USART_TXRX_State;			/* Specifies TX and RX states of selected USART */

	USART_ClockInitTypeDef USART_ClkSt; 	/* Specifies clock settings for selected USART */
	
} USART_InitTypeDef;

extern USART_InitTypeDef USART_CnfgSt;

/*
 * Functions prototypes 
 */
void USART_xInit(USART_t *USARTx , USART_InitTypeDef *USART_CnfgSt);
void USART_xConfigTX_RX(USART_t *USARTx,USART_TXRX_t Copy_xState);
void USART_vSendByte(USART_t *USARTx,uint8 data);
uint8 USART_u8GetByte(USART_t *USARTx);

#endif  __USART_INTERFACE_H__
