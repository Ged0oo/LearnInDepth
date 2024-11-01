/* 
 * File:   RCC_program.c
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 30, 2024, 8:41 PM
 */

#include "RCC_interface.h"
#include "RCC_config.h"
#include "RCC_private.h"

const uint8 APBPrescaler[8] 	= 	{1,1,1,1,2,4,8,16};
const uint16 AHBPrescaler[16] 	= 	{1,1,1,1,1,1,1,1,2,4,8,16,64,128,256,512};

RCC_Config_t RCC_obj =
{
	.ClockSource = CLOCK_SOURCE_TYPE,
	.Prescaler.ABP1_Prescaler = ABP1_PRESCALER_TYPE,
	.Prescaler.ABP2_Prescaler = ABP2_PRESCALER_TYPE,
	.Prescaler.AHB_Prescaler  = AHB_PRESCALER_TYPE
};

static void RCC_voidClockSource(uint8 Copy_u8xClock);
static void RCC_voidBus_Prescaler(RCC_Config_t *Copy_u8RCC_Config);
static void RCC_voidPLL_Mul(uint8 Copy_u8xMul_Factor);
static void RCC_voidClockSource(uint8 Copy_u8xClock);
static void RCC_voidPLL_Clock_Source(uint8 Copy_u8xPLL_Source);

void MRCC_voidClockInit(RCC_Config_t *RCC_Config)
{
	if(NULL == RCC_Config)
	{
		return;
	}
	else
	{
		RCC_voidClockSource(RCC_Config->ClockSource);
		if(RCC_Config->ClockSource == RCC_PLL)
		{
			RCC_voidPLL_Clock_Source(RCC_Config->PLL_Config.PLL_Source);
			RCC_voidPLL_Mul(RCC_Config->PLL_Config.PLL_Mul_Factor);
		}
		else if(RCC_Config->ClockSource == RCC_HSI)
		{
			/* HSI Trim function*/
		}
		/* Adjust Prescaler */
		RCC_voidBus_Prescaler(RCC_Config);
	}
}

void MRCC_voidPeripheralClockEnable(uint8 Copy_u8BusName, RCC_Peripheral_t Copy_u8PeripheralName)
{
	switch(Copy_u8BusName)
	{
	case RCC_AHB_BUS:
		SET_BIT(RCC->AHBENR,Copy_u8PeripheralName);
		break;

	case RCC_APB1_BUS:
		SET_BIT(RCC->APB1ENR,Copy_u8PeripheralName);
		break;

	case RCC_APB2_BUS:
		SET_BIT(RCC->APB2ENR,Copy_u8PeripheralName);
		break;

	default:
		/* return error */
		break;
	}
}

void MRCC_voidPeripheralClockDisable(uint8 Copy_u8BusName, RCC_Peripheral_t Copy_u8PeripheralName)
{
	switch(Copy_u8BusName)
	{
		case RCC_AHB_BUS :
			CLEAR_BIT(RCC->AHBENR,Copy_u8PeripheralName);
			break;

		case RCC_APB1_BUS :
			CLEAR_BIT(RCC->APB1ENR,Copy_u8PeripheralName);
			break;

		case RCC_APB2_BUS :
			CLEAR_BIT(RCC->APB2ENR,Copy_u8PeripheralName);
			break;

		default:
			/* return error */
			break;
	}

}

static void RCC_voidClockSource(uint8 Copy_u8xClock)
{
	/*First clear configuration bits*/
	CLEAR_BIT(RCC->CFGR , 0);
	CLEAR_BIT(RCC->CFGR , 1);

	/*Choose clock source*/
	switch(Copy_u8xClock)
	{
	/* Internal clock*/
	case RCC_HSI:
		/*Set HSION BIT*/
		SET_BIT(RCC->CR , 0);
		/*Wait until the clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR , 1));
		
		/* Select HSI as clock source */
		CLEAR_BIT(RCC->CFGR , 0);
		CLEAR_BIT(RCC->CFGR , 1);
		break;

		/*External clock*/
	case RCC_HSE :
		/* Set HSEON BIT */
		SET_BIT(RCC->CR , 16);
		/* Check if Bypass is on */
		#if RCC_HSE_BYPASS == HSE_BYPASS_OFF_CRYSTAL
				CLEAR_BIT(RCC->CR , 18);
		#elif RCC_HSE_BYPASS == HSE_BYPASS_ON_RC
				SET_BIT(RCC->CR , 18);
		#endif
		/*Wait until external clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR , 17));

		/* Select HSE as clock source */
		SET_BIT(RCC->CFGR , 0);
		CLEAR_BIT(RCC->CFGR , 1);
		break;

		/*PLL clock*/
	case RCC_PLL:
		/* Set PLLON BIT */
		SET_BIT(RCC->CR , 24);
		/*Wait until PLL clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR , 25));

		CLEAR_BIT(RCC->CFGR , 0);
		SET_BIT(RCC->CFGR , 1);
		break;

		/* default HSI will be used */
	default:
		/*Set HSION BIT*/
		SET_BIT(RCC->CR , 0);
		/*Wait until the clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR , 1));
		
		/* Select HSI as clock source */
		CLEAR_BIT(RCC->CFGR , 0);
		CLEAR_BIT(RCC->CFGR , 1);
		break;
	}
}

static void RCC_voidPLL_Clock_Source(uint8 Copy_u8xPLL_Source)
{
	/* First Clear the Bits */
	CLEAR_BIT(RCC->CFGR,17);
	CLEAR_BIT(RCC->CFGR,16);

	switch(Copy_u8xPLL_Source)
	{
		case PLL_SRC_HSE_NOT_DEVIDED:
			/* Set HSEON BIT */
			SET_BIT(RCC->CR,16);
			/*Wait until external clock is stable*/
			while(BIT_IS_CLEAR(RCC->CR,17));

			/*Select HSE as PLL source*/
			CLEAR_BIT(RCC->CFGR,17);
			SET_BIT(RCC->CFGR,16);
			
			/*Wait until external clock is stable*/
			while(BIT_IS_CLEAR(RCC->CR,17));
			break;
			
		case PLL_SRC_HSE_DEVIDED_BY_2:
			/* Set HSEON BIT */
			SET_BIT(RCC->CR,16);
			/*Wait until external clock is stable*/
			while(BIT_IS_CLEAR(RCC->CR,17));

			/*Select HSE as PLL source*/
			SET_BIT(RCC->CFGR,17);
			SET_BIT(RCC->CFGR,16);
			/*Wait until external clock is stable*/
			while(BIT_IS_CLEAR(RCC->CR,17));
			break;
			
		case PLL_SRC_HSI_DEVIDED_BY_2:
			/*Set HSION BIT*/
			SET_BIT(RCC->CR,0);
			/*Wait until the clock is stable*/
			while(BIT_IS_CLEAR(RCC->CR,1));

			CLEAR_BIT(RCC->CFGR,16);
			break;
			
			/* default the PLL clock source is internal clock */
		default:
			/*Set HSION BIT*/
			SET_BIT(RCC->CR,0);
			/*Wait until the clock is stable*/
			while(BIT_IS_CLEAR(RCC->CR,1));
			break;
	}
}

static void RCC_voidPLL_Mul(uint8 Copy_u8xMul_Factor)
{
	RCC->CFGR |= (Copy_u8xMul_Factor << 18);
}

static void RCC_voidBus_Prescaler(RCC_Config_t *Copy_u8RCC_Config)
{
	if(NULL == Copy_u8RCC_Config)
	{
		return;
	}
	else
	{
		RCC->CFGR |= ((Copy_u8RCC_Config->Prescaler.AHB_Prescaler)  << 4);
		RCC->CFGR |= ((Copy_u8RCC_Config->Prescaler.ABP1_Prescaler) << 8);
		RCC->CFGR |= ((Copy_u8RCC_Config->Prescaler.ABP2_Prescaler) << 11);
	}
}

void RCC_xGetAPB2_Freq(uint32 *pu32Freq)
{
	switch(RCC_obj.Prescaler.ABP2_Prescaler)
	{
		case APB2_NOT_DEVIDED:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY;
			break;

		case APB2_DIVIDED_BY_2:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 2;
			break;

		case APB2_DIVIDED_BY_4:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 4;
			break;

		case APB2_DIVIDED_BY_8:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 8;
			break;

		case APB2_DIVIDED_BY_16:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 16;
			break;

		default:
			*pu32Freq	=	0;
	}
}

void RCC_xGetAPB1_Freq(uint32 *pu32Freq)
{
	switch(RCC_obj.Prescaler.ABP1_Prescaler)
	{
		case APB1_NOT_DEVIDED:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY;
			break;

		case APB1_DIVIDED_BY_2:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 2;
			break;

		case APB1_DIVIDED_BY_4:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 4;
			break;

		case APB1_DIVIDED_BY_8:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 8;
			break;

		case APB1_DIVIDED_BY_16:
			*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 16;
			break;

		default:
			*pu32Freq	=	0;
			break;
	}
}

uint32 MRCC_GetSYSCLK()
{
	switch((RCC->CFGR >> 2) & 0b11)
	{
		case 0:
			return HSI_RC_CLK;
			break;

		case 1:
			return HSE_CLK;
			break;

		case 2:
		default :
			return 16000000;
			break;
	}
}

uint32 MRCC_GetHCLK()
{
	// Bits 7:4 HPRE: AHB pre-scaler
	uint32 clk = MRCC_GetSYSCLK() / AHBPrescaler[(RCC->CFGR & (0xf << 4)) >> 4];
	return clk;
}

uint32 MRCC_GetPCLK1()
{
	// Bits 10:8 PPRE1: APB low-speed pre-scaler (APB1)
	uint32 clk =  MRCC_GetHCLK() / APBPrescaler[(RCC->CFGR & 0b111<<8)>>8];
	return clk;
}

uint32 MRCC_GetPCLK2()
{
	// Bits 13:11 PPRE2: APB high-speed pre-scaler (APB2)
	uint32 clk =  MRCC_GetHCLK() / APBPrescaler[(RCC->CFGR & 0b111<<11)>>11];
	return clk;
}

