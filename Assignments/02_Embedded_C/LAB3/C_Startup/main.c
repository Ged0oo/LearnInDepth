#include "PlatformTypes.h"

#define RCC_BASE		0x40021000
#define GPIOA_BASE		0x40010800

#define APB2ENR_OFFSET 	0x18
#define CRH_OFFSET		0x04
#define	ODR_OFFSET		0x0C

#define APB2ENR_R		*(vuint32*)(RCC_BASE+APB2ENR_OFFSET)
#define CRH_R			*(vuint32*)(GPIOA_BASE+CRH_OFFSET)
#define ODR_R			*(vuint32*)(GPIOA_BASE+ODR_OFFSET)

void main(void)
{
	APB2ENR_R |= (1<<2);
	CRH_R = (CRH_R&0xFF0FFFFF) + 0x00200000;
		
	while(1)
	{
		ODR_R |= (1<<13);
		for(uint16 i=0 ; i<10000 ; i++);
		ODR_R &= ~(1<<13);
		for(uint16 i=0 ; i<10000 ; i++);
	}
}