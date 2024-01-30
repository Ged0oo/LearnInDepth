/* 
 * File:   TEMPLATE_INTERFACE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 29, 2024, 8:41 PM
 */

#ifndef __TEMPLATE_INTERFACE_H__
#define __TEMPLATE_INTERFACE_H__

typedef enum 
{
	AFIO_PORTA = 0, 
	AFIO_PORTB    ,
	AFIO_PORTC    ,
	AFIO_PORTD    ,
	AFIO_PORTE    ,
	AFIO_PORTF    ,
	AFIO_PORTG     
}AFIO_Port_t ; 

typedef enum 
{
	AFIO_LINE0 = 0, 
	AFIO_LINE1    , 
	AFIO_LINE2    , 
	AFIO_LINE3    , 
	AFIO_LINE4    , 
	AFIO_LINE5    , 
	AFIO_LINE6    , 
	AFIO_LINE7    , 
	AFIO_LINE8    , 
	AFIO_LINE9    ,
	AFIO_LINE10   , 
	AFIO_LINE11   , 
	AFIO_LINE12   , 
	AFIO_LINE13   , 
	AFIO_LINE14   ,
	AFIO_LINE15   , 
	AFIO_LINE16   , 
	AFIO_LINE17   , 
	AFIO_LINE18   , 
	AFIO_LINE19    
}AFIO_Line_t;

void AFIO_vEXTI_Configuration(AFIO_Line_t Copy_u8Line, AFIO_Port_t Copy_u8Port);  

#endif  __TEMPLATE_INTERFACE_H__