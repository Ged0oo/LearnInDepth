/* 
 * File:   SPI_CONFIG.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on Febreuary 16, 2024, 8:41 PM
 */


#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#define SPI_APP_MASTER
//#define SPI_APP_SLAVE

#include "GPIO_interface.h"

#define SPI_CONFIGURED_BR_PRESCALER				SPI_BAUDERATE_PRESCALER_8
#define SPI_CONFIGURED_DataSize					SPI_DATA_SIZE_8BIT
#define SPI_CONFIGURED_FrameFormat				SPI_FRAME_MSB_FIRST
#define SPI_CONFIGURED_COMMUNICATION_MODE		SPI_COMMUNICATION_MODE_TWO_LINE_FULL_DUPLEX
#define SPI_CONFIGURED_ClockPolarity			SPI_CLOCK_POLARITY_IDLE_HIGH
#define SPI_CONFIGURED_ClockPhase				SPI_CLOCK_PHASE_SECOND_EDGE

#ifdef SPI_APP_MASTER
#define SPI_CONFIGURED_MODE						SPI_MASTER_MODE
#define SPI_CONFIGURED_NSS						SPI_NSS_SW_MASTER
#define SPI_CONFIGURED_IRQ_ENABLE				SPI_IRQ_Enable_None
#define SPI_CONFIGURED_IRQ_CALLBACK				NULL
#endif

#ifdef SPI_APP_SLAVE
#define SPI_CONFIGURED_MODE						SPI_SLAVE_MODE
#define SPI_CONFIGURED_NSS						SPI_NSS_HW_SLAVE
#define SPI_CONFIGURED_IRQ_ENABLE				SPI_IRQ_Enable_None
#define SPI_CONFIGURED_IRQ_CALLBACK				NULL
#endif


#define SPI_N_SLAVES							(1)
static uint8 SPI_SlavesNum = SPI_N_SLAVES;

#define SPI_FRAME_SIZE_DATA_TYPE				uint8

#define SPI_CLK_PORT							GPIOA
#define SPI_CLK_PIN								GPIO_PIN_5

#define SPI_MISO_PORT							GPIOA
#define SPI_MISO_PIN							GPIO_PIN_6

#define SPI_MOSI_PORT							GPIOA
#define SPI_MOSI_PIN							GPIO_PIN_7

typedef struct
{
	GPIO_t *    SlavePort;
	GPIO_t *	SlavePin;
}SPI_Map;

SPI_Map SPI_MapCnfg[SPI_N_SLAVES] =
{
	{GPIOA, GPIO_PIN_4}
};

#endif  __SPI_CONFIG_H__
