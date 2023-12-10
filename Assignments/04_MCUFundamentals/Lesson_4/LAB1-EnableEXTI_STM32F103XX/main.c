// LAB1 Enable External Interrupt for STM32F103XX

#define GPIOA_BASE	 	0x40010800
#define GPIOA_CRL	 	*((volatile unsigned long *)(0x00 + GPIOA_BASE))
#define GPIOA_CRH	 	*((volatile unsigned long *)(0x04 + GPIOA_BASE))
#define GPIOA_ODR	 	*((volatile unsigned long *)(0x0C + GPIOA_BASE))
	
#define RCC_BASE	 	0x40021000
#define RCC_CR		 	*((volatile unsigned long *)(0x00 + RCC_BASE))
#define RCC_CFGR	 	*((volatile unsigned long *)(0x04 + RCC_BASE))
#define RCC_APB2RSTR 	*((volatile unsigned long *)(0x0C + RCC_BASE))
#define RCC_APB2ENR	 	*((volatile unsigned long *)(0x18 + RCC_BASE))

#define AFIO_BASE	  	0x40010000
#define AFIO_EXTICR1  	*((volatile unsigned long *)(0x08 + AFIO_BASE))

#define EXTI_BASE	  	0x40010400
#define EXTI_IMR  		*((volatile unsigned long *)(0x00 + EXTI_BASE))
#define EXTI_EMR  		*((volatile unsigned long *)(0x04 + EXTI_BASE))
#define EXTI_RTSR  		*((volatile unsigned long *)(0x08 + EXTI_BASE))
#define EXTI_PR  		*((volatile unsigned long *)(0x14 + EXTI_BASE))


#define NVIC_ISER0  	*((volatile unsigned long *)(0xE000E100))


void main(void)
{
	// RCC Init PORTA, AFIO
	RCC_APB2ENR  |= (1<<2);
	RCC_APB2RSTR |= (1<<0);
	
	// GPIOA is Configured
	GPIOA_CRL |= (1 << 2);
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	
	// Enable EXTI0 Line to be Connected with GPIOA0
	AFIO_EXTICR1 |= (0<<0);
	
	// Configure the Trigger Detection (Rising) for EXTI0
	EXTI_RTSR |= (1<<0);	
	
	// Event Mask Register
	EXTI_IMR |= (1<<0);
	
	// Enable NVIC IRQ6
	NVIC_ISER0 |= (1<<6);
	
	while(1);
}

void EXTI0_IRQHandler(void)
{
	GPIOA_ODR ^= (1<<13);
	EXTI_PR |= (1<<0);
}