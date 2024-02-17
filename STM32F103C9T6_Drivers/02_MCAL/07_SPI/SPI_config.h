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


#define SPI_CONFIGURED_BI_MODE					SPI_TWO_LINES_UNIDIR_MODE
#define SPI_CONFIGURED_BR						SPI_BR_Prescaler_8
#define SPI_CONFIGURED_CRCState					SPI_DISABLE_CRC
#define SPI_CONFIGURED_CRCPhase					SPI_NO_CRC_PHASE
#define SPI_CONFIGURED_DataFrame				SPI_8_BIT_DATA_FRAME
#define SPI_CONFIGURED_TransDir					SPI_SIMPLEX_RECV
#define SPI_CONFIGURED_SlaveMng					SPI_DISABLE_SLAVE_MNG
#define SPI_CONFIGURED_SlavePinState			SPI_SSI_LOW
#define SPI_CONFIGURED_FrameFormat				SPI_MSB_FIRST
#define SPI_CONFIGURED_State					SPI_ENABLE
#define SPI_CONFIGURED_MSTR						SPI_MASTER
#define SPI_CONFIGURED_CPol						SPI_CPOL_LOW
#define SPI_CONFIGURED_CPhase					SPI_CPHA_First_Edge


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
