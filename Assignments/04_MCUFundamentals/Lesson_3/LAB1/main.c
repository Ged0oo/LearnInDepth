// LAB1 Toggle port A pin 13

typedef 	volatile unsigned long        vuint32;
typedef 	unsigned long                 uint32;

#define GPIOA_BASE	0x40010800
#define GPIOA_CRH	*((volatile unsigned long *)(0x04 + GPIOA_BASE))
#define GPIOA_ODR	*((volatile unsigned long *)(0x0C + GPIOA_BASE))

#define RCC_BASE	0x40021000
#define RCC_APB2ENR	*((volatile unsigned long *)(0x18 + RCC_BASE))


void main(void)
{
	// GPIO Init
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	// RCC Init PORTA
	RCC_APB2ENR |= (1<<2);

	while(1)
	{
		GPIOA_ODR ^= (1<<13);
		for(long delay = 0 ; delay <1000 ; delay++);
	}
}
