/* 
 * File:   EXTI_PRIVATE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 29, 2024, 8:41 PM
 */

#ifndef __EXTI_PRIVATE_H__
#define __EXTI_PRIVATE_H__
	
#define EXTI_BASE_ADDRESS				0x40010400

typedef struct
{
  volatile uint32 IMR;
  volatile uint32 EMR;
  volatile uint32 RTSR;
  volatile uint32 FTSR;
  volatile uint32 SWIER;
  volatile uint32 PR;
}EXTI_t;

#define EXTI							((EXTI_t*)EXTI_BASE_ADDRESS)
	
#endif  __EXTI_PRIVATE_H__