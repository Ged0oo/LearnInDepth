/* 
 * File:   SPI_PROGRAM.c
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on Febreuary 16, 2024, 8:41 PM
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"


SPI_Config_t spiCFG =
{
		.BIModeState = SPI_CONFIGURED_BI_MODE,
		.BaudRate = SPI_CONFIGURED_BR,
		.CRC_State = SPI_CONFIGURED_CRCState,
		.CRC_TransNextState = SPI_CONFIGURED_CRCPhase,
		.ClockPhase = SPI_CONFIGURED_CPhase,
		.ClockPolarity = SPI_CONFIGURED_CPol,
		.FrameFormatState = SPI_CONFIGURED_FrameFormat,
		.FrameSize =  SPI_CONFIGURED_DataFrame,
		.MasterSelection = SPI_CONFIGURED_MSTR,
		.SPI_State = SPI_CONFIGURED_State,
		.SlaveMngState = SPI_CONFIGURED_SlaveMng,
		.SlavePinState = SPI_CONFIGURED_SlavePinState,
		.TransMode = SPI_CONFIGURED_TransDir
};


/*
 * Current slave management state
 */
static SPI_SlaveMng_t SPI_SlaveMmg;


static void SPI_xSetBidMode( SPI_t* SPIx,SPI_BidMode_t Copy_xMode);
static void SPI_xEnableCRC( SPI_t* SPIx,SPI_CRCState_t Copy_xOutPutState);
static void SPI_xSetCRCPhase( SPI_t* SPIx,SPI_CRCPhase_t Copy_xCRCState);
static void SPI_xSetDataFrameSize( SPI_t* SPIx,SPI_DataFrame_t Copy_xDataLength);
static void SPI_xSetTransferDir(SPI_t* SPIx,SPI_TransDir_t Copy_xDataLength);
static void SPI_xSetSwSlaveMng(SPI_t* SPIx,SPI_SlaveMng_t Copy_xDataLength);
static void SPI_xSetFrameFormat(SPI_t* SPIx,SPI_FrameFormat_t Copy_xFormat);
static void SPI_xSetBaudRate(SPI_t* SPIx,uint16 Copy_u16BaudRate);
static void SPI_xSelectMaster(SPI_t* SPIx,SPI_MSTR_t Copy_xState);
static void SPI_xSetClkPolarity(SPI_t* SPIx,SPI_CPol_t Copy_xClockPolarityState);
static void SPI_xSetClkPhase(SPI_t* SPIx,SPI_CPhase_t Copy_xClockPhaseState);


void MCAL_SPI_xInit(SPI_t* SPIx,const SPI_Config_t *SPIx_Cnfg)
{
	uint8 Local_u8Index	= 0;

	/*
	 * Set BI direction mode
	 */
	SPI_xSetBidMode(SPIx,SPIx_Cnfg->BIModeState);
	
	/*
	 * Set CRC
	 */
	SPI_xEnableCRC(SPIx,SPIx_Cnfg->CRC_State);
	
	/*
	 * Set CRC phase
	 * */
	SPI_xSetCRCPhase(SPIx,SPIx_Cnfg->CRC_TransNextState);
	
	/*
	 * Set data frame size
	 * */
	SPI_xSetDataFrameSize(SPIx,SPIx_Cnfg->FrameSize);
	
	/*
	 * Set transmission direction
	 *  */
	SPI_xSetTransferDir(SPIx,SPIx_Cnfg->TransMode);
	
	/*
	 * Set slave management state
	 * */
	SPI_xSetSwSlaveMng(SPIx,SPIx_Cnfg->SlaveMngState);
	
	/*
	 * Set slave pin state
	 * */
	SPI_xSetSwSlavePin(SPIx,SPIx_Cnfg->SlavePinState);
	
	/*
	 * Set frame format (MSB OR LSB)
	 * */
	SPI_xSetFrameFormat(SPIx,SPIx_Cnfg->FrameFormatState);
	
	/*
	 * Set Baud rate
	 * */
	SPI_xSetBaudRate(SPIx,SPIx_Cnfg->BaudRate);
	
	/*
	 * Set Master selection (Master or Slave)
	 * */
	SPI_xSelectMaster(SPIx,SPIx_Cnfg->MasterSelection);
	
	/*
	 * Set clock polarity
	 * */
	SPI_xSetClkPolarity(SPIx,SPIx_Cnfg->ClockPolarity);
	
	/*
	 * Set clock phase
	 * */
	SPI_xSetClkPhase(SPIx,SPIx_Cnfg->ClockPhase);

	/*
	 * Initialize slave pins as output and make their ideal state is high
	 * */
	if(SPI_ENABLE_SLAVE_MNG	==	SPIx_Cnfg->SlaveMngState)
	{
		SPI_SlaveMmg	=	SPI_ENABLE_SLAVE_MNG;
		for(Local_u8Index = 0;Local_u8Index < SPI_SlavesNum;Local_u8Index++)
		{
			GPIO_vInitPortPin(SPI_MapCnfg[Local_u8Index].SlavePort,SPI_MapCnfg[Local_u8Index].SlavePin,GPIO_OUT);
			GPIO_vWritePortPin(SPI_MapCnfg[Local_u8Index].SlavePort,SPI_MapCnfg[Local_u8Index].SlavePin,GPIO_HIGH);
		}
	}

	/*
	 * Set SPI State (Disable / Enable)
	 * */
	SPI_xSetState(SPIx,SPIx_Cnfg->SPI_State);

	/*
	 * Initialize SPI pins
	 * */
	GPIO_vInitPortPin(SPI_CLK_PORT,SPI_CLK_PIN,GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_PUSHPULL_MODE_10MHZ);
	GPIO_vInitPortPin(SPI_MOSI_PORT,SPI_MOSI_PIN,GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_PUSHPULL_MODE_10MHZ);
	GPIO_vInitPortPin(SPI_MISO_PORT,SPI_MISO_PIN,GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_PUSHPULL_MODE_10MHZ);
}


void MCAL_SPI_SendData(SPI_t* SPIx,uint16 *p_Txbuffer)
{
	/*
	 * Wait for TX buffer is empty to send data
	 */
	while(!(SPIx->SR & 1<<1));
	SPIx->DR = *p_Txbuffer;
}


void MCAL_SPI_ReciveData(SPI_t* SPIx,uint16 *p_Txbuffer)
{
	/*
	 * Wait for RX buffer is not empty to send data
	 */
	while(!(SPIx->SR & 1<<0));
	*p_Txbuffer = SPIx->DR;
}


void MCAL_SPI_xSetState(SPI_t* SPIx,SPI_State_t Copy_xState)
{
	switch(Copy_xState)
	{
		case SPI_DISABLE:
			CLEAR_BIT(SPIx->CR1,6);
			break;
			
		case SPI_ENABLE:
			SET_BIT(SPIx->CR1,6);
			break;
			
		default:
			break;
	}
}


void MCAL_SPI_xSetSwSlavePin(SPI_t* SPIx,SPI_SlavePinState_t Copy_xSSI_State)
{
	/*
	 * This bit has an effect only when the SSM bit is set.
	 * The value of this bit is forced onto the
	 * NSS pin and the IO value of the NSS pin is ignored
	 * */
	switch(Copy_xSSI_State)
	{
		case SPI_SSI_LOW:
			CLEAR_BIT(SPIx->CR1,8);
			break;
			
		case SPI_SSI_HIGH:
			SET_BIT(SPIx->CR1,8);
			break;
			
		default:
			break;
	}
}


void SPI_xSetBidMode( SPI_t* SPIx,SPI_BidMode_t Copy_xMode)
{
	switch(Copy_xMode)
	{
		case SPI_TWO_LINES_UNIDIR_MODE:
			CLEAR_BIT(SPIx->CR1,15);
			CLEAR_BIT(SPIx->CR1,14);
			break; 
			
		case SPI_ONE_LINE_BIDIR_MODE_OUTPUT_DISABLE:
			SET_BIT(SPIx->CR1,15);
			CLEAR_BIT(SPIx->CR1,14);
			break;
			
		case SPI_ONE_LINE_BIDIR_MODE_OUTPUT_ENABLE_OUTPUT:
			SET_BIT(SPIx->CR1,15);
			SET_BIT(SPIx->CR1,14);
			break;
			
		default:
			break;
	}
}


void SPI_xEnableCRC( SPI_t* SPIx,SPI_CRCState_t Copy_xOutPutState)
{
	switch(Copy_xOutPutState)
	{
		case SPI_DISABLE_CRC:
			CLEAR_BIT(SPIx->CR1,13);
			break;
			
		case SPI_ENABLE_CRC:
			SET_BIT(SPIx->CR1,13);
			break;
			
		default:
			break;
	}
}


void SPI_xSetCRCPhase( SPI_t* SPIx,SPI_CRCPhase_t Copy_xCRCState)
{
	switch(Copy_xCRCState)
	{
		case SPI_NO_CRC_PHASE:
			CLEAR_BIT(SPIx->CR1,12);
			break;
			
		case SPI_CRC_PHASE:
			SET_BIT(SPIx->CR1,12);
			break;
			
		default:
			break;
	}
}


void SPI_xSetDataFrameSize( SPI_t* SPIx,SPI_DataFrame_t Copy_xDataLength)
{
	switch(Copy_xDataLength)
	{
		case SPI_8_BIT_DATA_FRAME:
			CLEAR_BIT(SPIx->CR1,11);
			break;
			
		case SPI_16_BIT_DATA_FRAME:
			SET_BIT(SPIx->CR1,11);
			break;
			
		default:
			break;
	}
}


void SPI_xSetTransferDir(SPI_t* SPIx,SPI_TransDir_t Copy_xDataLength)
{
	switch(Copy_xDataLength)
	{
		case SPI_FULL_DUPLEX:
			CLEAR_BIT(SPIx->CR1,10);
			break;
			
		case SPI_SIMPLEX_RECV:
			SET_BIT(SPIx->CR1,10);
			break;
			
		default:
			break;
	}
}


void SPI_xSetSwSlaveMng(SPI_t* SPIx,SPI_SlaveMng_t Copy_xDataLength)
{
	switch(Copy_xDataLength)
	{
		case SPI_DISABLE_SLAVE_MNG:
			CLEAR_BIT(SPIx->CR1,9);
			break;
			
		case SPI_ENABLE_SLAVE_MNG:
			SET_BIT(SPIx->CR1,9);
			break;
			
		default:
			break;
	}
}


void SPI_xSetFrameFormat(SPI_t* SPIx,SPI_FrameFormat_t Copy_xFormat)
{
	switch(Copy_xFormat)
	{
		case SPI_MSB_FIRST:
			CLEAR_BIT(SPIx->CR1,7);
			break;
			
		case SPI_LSB_FIRST:
			SET_BIT(SPIx->CR1,7);
			break;
			
		default:
			break;
	}
}


void SPI_xSetBaudRate(SPI_t* SPIx,uint16 Copy_u16BaudRate)
{
	/*
	 * Clear selection bits
	 *  */
	SPIx->CR1 &= 0xFFC7;

	/*
	 * Assign baud rate
	 * */
	SPIx->CR1 |= Copy_u16BaudRate;
}


void SPI_xSelectMaster(SPI_t* SPIx,SPI_MSTR_t Copy_xState)
{
	switch(Copy_xState)
	{
		case SPI_SLAVE:
			CLEAR_BIT(SPIx->CR1,2);
			break;
			
		case SPI_MASTER:
			SET_BIT(SPIx->CR1,2);
			break;
			
		default:
			break;
	}	
}


void SPI_xSetClkPolarity(SPI_t* SPIx,SPI_CPol_t Copy_xClockPolarityState)
{
	switch(Copy_xClockPolarityState)
	{
		case SPI_CPOL_LOW:
			CLEAR_BIT(SPIx->CR1,1);
			break;
			
		case SPI_CPOL_HIGH:
			SET_BIT(SPIx->CR1,1);
			break;
			
		default:
			break;
	}	
}


void SPI_xSetClkPhase(SPI_t* SPIx,SPI_CPhase_t Copy_xClockPhaseState)
{
	switch(Copy_xClockPhaseState)
	{
		case SPI_CPHA_First_Edge:
			CLEAR_BIT(SPIx->CR1,0);
			break;

		case SPI_CPHA_Second_Edge:
			SET_BIT(SPIx->CR1,0);
			break;
			
		default:
			break;
	}	
}
