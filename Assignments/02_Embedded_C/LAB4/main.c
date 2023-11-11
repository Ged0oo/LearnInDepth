#include "PlatformTypes.h"

#define SYSCTL_RCGC2_R		*(vuint32 *)((vuint32*)(0x400FE108))
#define GPIO_PORTF_DATA_R	*(vuint32 *)((vuint32*)(0x400253FC))
#define GPIO_PORTF_DIR_R	*(vuint32 *)((vuint32*)(0x40025400))
#define GPIO_PORTF_DEN_R	*(vuint32 *)((vuint32*)(0x4002551C))

void main(void)
{
	uint32 delay;
	SYSCTL_RCGC2_R |= 0x20;
	
	for(delay =0 ; delay <300000 ; delay++);
	GPIO_PORTF_DEN_R |=(1<<3);	
	GPIO_PORTF_DIR_R |=(1<<3);	
	
	while(1)
	{
		GPIO_PORTF_DATA_R |=(1<<3); 
		for(delay =0 ; delay <10000 ; delay++); 
		
		GPIO_PORTF_DATA_R &=~(1<<3);
		for(delay =0 ; delay <10000 ; delay++);
	}
}