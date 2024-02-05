/* 
 * File:   RCC_config.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 30, 2024, 8:41 PM
 */

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

#include "RCC_interface.h"

/*      HSE ByPass define RCC_HSE_BYPASS         */
/* TWO MODES : HSE_BYPASS_OFF , HSE_BYPASS_ON    */
#define 		SYSTEM_CLOCK_FREQUENCY		8000000UL
#define 		RCC_HSE_BYPASS        		HSE_BYPASS_OFF
#define			CLOCK_SOURCE_TYPE			RCC_HSE
#define 		ABP1_PRESCALER_TYPE			APB1_NOT_DEVIDED
#define 		ABP2_PRESCALER_TYPE			APB2_NOT_DEVIDED
#define 		AHB_PRESCALER_TYPE			AHB_NOT_DEVIDED

#endif
