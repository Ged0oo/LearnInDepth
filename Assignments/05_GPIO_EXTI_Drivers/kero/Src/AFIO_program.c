/* 
 * File:   AFIO_PROGRAM.c
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 29, 2024, 8:41 PM
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"


void AFIO_vEXTI_Configuration(AFIO_Line_t Copy_u8Line, AFIO_Port_t Copy_u8Port)
{
	uint8 registerID = Copy_u8Line / 4;
	uint8 offset = Copy_u8Line % 4;
	uint8 shift = offset * 4;
	AFIO -> EXTICR[offset] &= ~(0xF << shift);
	AFIO -> EXTICR[offset] |=  (Copy_u8Port << shift);
}
