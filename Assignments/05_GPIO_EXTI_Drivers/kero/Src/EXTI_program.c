/* 
 * File:   EXTI_PROGRAM.c
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 29, 2024, 8:41 PM
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

static void (*EXTI_vEXTI_CallBack[19])(void);

void EXTI_vSetSignalLatch(uint8 Copy_u8EXTI_Line, uint8 Copy_u8EXTI_TrigerMode)
{
	switch(Copy_u8EXTI_TrigerMode)
	{
		case EXTI_TRIGGER_FALLING_EDGE:
			SET_BIT(EXTI->FTSR, Copy_u8EXTI_Line);
			break;
			
		case EXTI_TRIGGER_RISING_EDGE:
			SET_BIT(EXTI->RTSR, Copy_u8EXTI_Line);
			break;
			
		case EXTI_TRIGGER_ON_CHANGE:
			SET_BIT(EXTI->FTSR, Copy_u8EXTI_Line);
			SET_BIT(EXTI->RTSR, Copy_u8EXTI_Line);
			break;
			
		default:
			break;
	}

	/* 
	 *Enable EXTI for the user's liner
	 */
	EXTI_vEnableEXTI(Copy_u8EXTI_Line);
}

void EXTI_vDeInit(void)
{
	/* 
	 * All EXTI registers are DeInitialized
	 */
	EXTI->IMR  = 0x00000000;
	EXTI->EMR  = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->PR   = 0x000FFFFF;
}

void EXTI_vSetPendingEXTI(uint8 Copy_u8EXTI_Line)
{
	SET_BIT(EXTI->PR, Copy_u8EXTI_Line);
}

void EXTI_vEnableEXTI(uint8 Copy_u8EXTI_Line)
{
	SET_BIT(EXTI->IMR, Copy_u8EXTI_Line);
}

void EXTI_vDisableEXTI(uint8 Copy_u8EXTI_Line)
{
	CLEAR_BIT(EXTI->IMR, Copy_u8EXTI_Line);
}

uint8 EXTI_u8GetFlagStatus(uint8 Copy_u8EXTI_Line)
{
	uint8 LOC_u8LineFlagStatus = 0;
	LOC_u8LineFlagStatus = GET_BIT(EXTI->PR, Copy_u8EXTI_Line);
	return LOC_u8LineFlagStatus;
}

void EXTI_vSoftwareTrigger(uint8 Copy_u8EXTI_Line)
{
	SET_BIT(EXTI->SWIER, Copy_u8EXTI_Line);
}

void EXTI_vSetCallBack(uint8 Copy_u8EXTI_Line, void(*Copy_vFuncPtr)(void))
{
	EXTI_vEXTI_CallBack[Copy_u8EXTI_Line] = Copy_vFuncPtr;
}

void EXTI0_IRQHandler(void)
{
	/*
	 * Execute callback function
	 */
	EXTI_vEXTI_CallBack[0]();
	
	/*
	 * Clear pending flag
	 */
	SET_BIT(EXTI->PR,EXTI_LINE0);
}

void EXTI1_IRQHandler(void)
{
	/* 
	 * Execute callback function
	 */
	EXTI_vEXTI_CallBack[1]();
	
	/*
	 * Clear pending flag
	 */
	SET_BIT(EXTI->PR,EXTI_LINE1);
}

void EXTI2_IRQHandler(void)
{
	/* 
	 * Execute callback function
	 */
	EXTI_vEXTI_CallBack[2]();
	
	/*
	 * Clear pending flag
	 */
	SET_BIT(EXTI->PR, EXTI_LINE2);
}

void EXTI3_IRQHandler(void)
{
	/* 
	 * Execute callback function
	 */
	EXTI_vEXTI_CallBack[3]();
	
	/*
	 * Clear pending flag
	 */
	SET_BIT(EXTI->PR, EXTI_LINE3);
}

void EXTI4_IRQHandler(void)
{
	/* 
	 * Execute callback function
	 */
	EXTI_vEXTI_CallBack[4]();
	
	/*
	 * Clear pending flag
	 */
	SET_BIT(EXTI->PR, EXTI_LINE4);
}

void EXTI9_5_IRQHandler(void)
{
	/* 
	 * Execute callback function
	 */
	EXTI_vEXTI_CallBack[9]();
	
	/*
	 * Clear pending flag
	 */
	SET_BIT(EXTI->PR, EXTI_LINE9);
}

void EXTI15_10_IRQHandler(void)
{
	/* 
	 * Execute callback function
	 */
	EXTI_vEXTI_CallBack[15]();
	
	/*
	 * Clear pending flag
	 */
	SET_BIT(EXTI->PR, EXTI_LINE15);
}
