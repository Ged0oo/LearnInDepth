/* 
 * File:   SPI_INTERFACE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on Febreuary 16, 2024, 8:41 PM
 */

#ifndef __SPI_INTERFACE_H__
#define __SPI_INTERFACE_H__

#include "SPI_private.h"
#include "NVIC_private.h".h"


/*
 * SPI Clock Enable
 */
#define SPI_ENABLE  		(1<<6)
#define SPI_DISABLE	    	(0<<6)

/*
 * SPI Clock Enable
 */
#define SPI1_CLK_EN()  		(RCC->APB2ENR |= 1<<12)
#define SPI2_CLK_EN()    	(RCC->APB1ENR |= 1<<14)


/*
 * SPI IRQs
 */
#define NVIC_IRQ35_SPI1_Enable()		NVIC_ISER1 |=1<<3
#define NVIC_IRQ36_SPI2_Enable()		NVIC_ISER1 |=1<<4
#define NVIC_IRQ35_SPI1_Disable()		NVIC_ICER1 |=1<<3
#define NVIC_IRQ36_SPI2_Disable()		NVIC_ICER1 |=1<<4

/*
 * SPI IRQ Sources
 */
typedef struct
{
	uint8 TXE : 1;
	uint8 RXE : 1;
	uint8 ERRI : 1;
	uint8 RES : 8;
}IRQSource_t;

/*
 * Polling Mechanism ability
 */
typedef enum
{
	Disable,
	Enable
}Polling_e;

/*
 * SPI Configuration Structure
 */
typedef struct
{
	uint16				Mode;
	uint16				CommunicationMode;
	uint16				FrameFormat;
	uint16				DataSize;
	uint16				ClockPolarity;
	uint16				ClockPhase;
	uint16				NSS;
	uint16				BRPrescaller;
	uint16				IRQEnable;
	void(*IRQ_CallBack)(IRQSource_t _irq);
}SPI_Config_t;
extern SPI_Config_t SPIx_Cnfg;

/*
 * SPI Mode define
 */
#define SPI_MASTER_MODE					(1<<2)
#define SPI_SLAVE_MODE					(0<<2)

/*
 * SPI Communication Mode define
 */
#define SPI_COMMUNICATION_MODE_TWO_LINE_FULL_DUPLEX			(0)
#define SPI_COMMUNICATION_MODE_TWO_RX						(1<<10)
#define SPI_COMMUNICATION_MODE_ONE_TX						(1<<15 | 1<<14)
#define SPI_COMMUNICATION_MODE_ONE_RX						(1<<15)

/*
 * SPI Frame Format define
 */
#define 	SPI_FRAME_MSB_FIRST				(0<<7)
#define 	SPI_FRAME_LSB_FIRST				(1<<7)

/*
 * Data Size define
 */
#define 	SPI_DATA_SIZE_8BIT			(0<<11)
#define 	SPI_DATA_SIZE_16BIT			(1<<11)


/*
 * SPI Clock Polarity define
 */
#define		SPI_CLOCK_POLARITY_IDLE_LOW		(0<<1)
#define		SPI_CLOCK_POLARITY_IDLE_HIGH	(1<<1)

/*
 * SPI Clock Phase define
 */
#define		SPI_CLOCK_PHASE_FIRST_EDGE		(0<<0)
#define		SPI_CLOCK_PHASE_SECOND_EDGE		(1<<0)

/*
 * SPI NSS define
 */
#define 	SPI_NSS_HW_SLAVE					(0)
#define 	SPI_NSS_HW_MASTER_OUT				(1<<2)
#define 	SPI_NSS_HW_MASTER_IN				(0)
#define 	SPI_NSS_SW_SLAVE					(1<<9)
#define 	SPI_NSS_SW_MASTER					(1<<9 | 1<<8)

/*
 * SPI Baud Rate Prescallers define
 */
#define SPI_BAUDERATE_PRESCALER_2 		0
#define SPI_BAUDERATE_PRESCALER_4		1<<3
#define SPI_BAUDERATE_PRESCALER_8		2<<3
#define SPI_BAUDERATE_PRESCALER_16 		3<<3
#define SPI_BAUDERATE_PRESCALER_32 		4<<3
#define SPI_BAUDERATE_PRESCALER_64 		5<<3
#define SPI_BAUDERATE_PRESCALER_128 	6<<3
#define SPI_BAUDERATE_PRESCALER_256 	7<<3

/*
 * SPI IRQ Enable define
 */
#define SPI_IRQ_Enable_None			0
#define SPI_IRQ_Enable_TXEIE		1<<7
#define SPI_IRQ_Enable_RXNEIE		1<<6
#define SPI_IRQ_Enable_ERRIE		1<<5

void MCAL_SPI_Init(SPI_t* SPIx, SPI_Config_t* SPI_Config);
void MCAL_SPI_DeInit(SPI_t* SPIx);
void MCAL_SPI_ConigureSlavePins(SPI_t* SPIx, SPI_Config_t *SPIx_Cnfg);
void MCAL_SPI_ConigurePins(SPI_t* SPIx, SPI_Config_t *SPIx_Cnfg);
void MCAL_SPI_SendData(SPI_t* SPIx, uint16* p_Txbuffer, Polling_e Polling);
void MCAL_SPI_ReceiveData(SPI_t* SPIx, uint16* p_Rxbuffer, Polling_e Polling);
void MCAL_SPI_TX_RX(SPI_t* SPIx, uint16* p_buffer, Polling_e Polling);

#endif  __SPI_INTERFACE_H__
