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

typedef uint8				SPI_BidMode_t;
typedef uint8				SPI_CRCState_t;
typedef uint8				SPI_CRCPhase_t;
typedef uint8				SPI_DataFrame_t;
typedef uint8				SPI_TransDir_t;
typedef uint8				SPI_SlaveMng_t;
typedef uint8				SPI_SlavePinState_t;
typedef uint8				SPI_FrameFormat_t;
typedef uint8				SPI_State_t;
typedef uint8				SPI_MSTR_t;
typedef uint8				SPI_CPol_t;
typedef uint8				SPI_CPhase_t;
typedef uint8				SPI_Data_t;
typedef uint8				SPI_SlaveNum_t;

/* 
 * SPI Baud rate Pre-scalers 
 */
#define SPI_BR_Prescaler_2				((uint16)0x0000)
#define SPI_BR_Prescaler_4				((uint16)0x0008)
#define SPI_BR_Prescaler_8				((uint16)0x0010)
#define SPI_BR_Prescaler_16 			((uint16)0x0018)
#define SPI_BR_Prescaler_32 			((uint16)0x0020)
#define SPI_BR_Prescaler_64 			((uint16)0x0028)
#define SPI_BR_Prescaler_128			((uint16)0x0030)
#define SPI_BR_Prescaler_256			((uint16)0x0038)

/* 
 * Direction modes 
 */
#define SPI_TWO_LINES_UNIDIR_MODE							(0)
#define SPI_ONE_LINE_BIDIR_MODE_OUTPUT_DISABLE				(1)
#define SPI_ONE_LINE_BIDIR_MODE_OUTPUT_ENABLE_OUTPUT		(2)

/* 
 * SPI CRC states 
 */
#define SPI_DISABLE_CRC						(0)
#define SPI_ENABLE_CRC						(1)

/* 
 * SPI CRC Phases 
 */
#define SPI_NO_CRC_PHASE					(0)
#define SPI_CRC_PHASE						(1)
		
/* 
 * SPI Size of frame 
 */
#define SPI_8_BIT_DATA_FRAME				(0)
#define SPI_16_BIT_DATA_FRAME				(1)
		
/* 
 * SPI data transfer modes 
 */
#define SPI_FULL_DUPLEX						(0)
#define SPI_SIMPLEX_RECV					(1)
		
/* 
 * SPI Receiving states 
 */
#define SPI_DISABLE_SLAVE_MNG				(0)
#define SPI_ENABLE_SLAVE_MNG				(1)

/* 
 * SPI slave select states 
 */
#define SPI_SSI_LOW							(0)
#define SPI_SSI_HIGH						(1)

/* 
 * SPI Frame format 
 */
#define	SPI_LSB_FIRST						(0)
#define	SPI_MSB_FIRST						(1)

/* 
 * SPI States 
 */
#define SPI_DISABLE							(0)
#define	SPI_ENABLE							(1)

/* 
 * SPI master selection 
 */
#define SPI_SLAVE							(0)
#define SPI_MASTER							(1)

/* 
 * SPI clock polarity states 
 */
#define SPI_CPOL_LOW 						(0)
#define SPI_CPOL_HIGH						(1)

/* 
 * SPI clock phases 
 */
#define SPI_CPHA_First_Edge 						(0)
#define SPI_CPHA_Second_Edge						(1)

typedef struct
{
	SPI_BidMode_t		BIModeState;
	SPI_CRCState_t		CRC_State;
	SPI_CRCPhase_t		CRC_TransNextState;
	SPI_DataFrame_t		FrameSize;
	SPI_TransDir_t		TransMode;
	SPI_SlaveMng_t		SlaveMngState;
	SPI_SlavePinState_t	SlavePinState;
	SPI_FrameFormat_t 	FrameFormatState;
	SPI_State_t			SPI_State;
	SPI_MSTR_t			MasterSelection;
	SPI_CPol_t			ClockPolarity;
	SPI_CPhase_t		ClockPhase;
	uint16				BaudRate;
}SPI_Config_t;

void SPI_xInit(SPI_t* SPIx,const SPI_Config_t *SPIx_Cnfg);
void SPI_xSetState(SPI_t* SPIx,SPI_State_t Copy_xState);
void SPI_xSetSwSlavePin(SPI_t* SPIx,SPI_SlavePinState_t Copy_xSSI_State);
void SPI_xSendRecieveSynch(SPI_t* SPIx,SPI_SlaveNum_t Copy_xSlaveNum,SPI_Data_t Copy_xSendData,SPI_Data_t *pxRecvData);


#endif  __SPI_INTERFACE_H__
