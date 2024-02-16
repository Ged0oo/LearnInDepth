/* 
 * File:   SPI_CONFIG.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on Febreuary 16, 2024, 8:41 PM
 */



#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include "GPIO_interface.h"

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
	{GPIOA, GPIO_PIN_0}
};

#endif  __SPI_CONFIG_H__
