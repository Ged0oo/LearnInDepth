/* 
 * File:   AFIO_PRIVATE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 29, 2024, 8:41 PM
 */

#ifndef __AFIO_PRIVATE_H__
#define __AFIO_PRIVATE_H__
	
#define AFIO_BASE_ADDRESS 0x40010000

typedef struct
{
 volatile uint32  EVCR; 
 volatile uint32  MAPR; 
 volatile uint32  EXTICR[4];
 volatile uint32  MAPR2; 
}AFIO_t;	
	
#define AFIO ((AFIO_t *) AFIO_BASE_ADDRESS)

#endif  __AFIO_PRIVATE_H__