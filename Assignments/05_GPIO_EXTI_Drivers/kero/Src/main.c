#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"

#define NVIC_ISER0  	*((volatile int *)(0xE000E100))

GPIO_ConfigType pin0 =
{
		.GPIO_PinMode = GPIO_PIN_INPUT_FLOATING_MODE,
		.GPIOx = GPIOA,
		.GPIO_PinNumber = GPIO_PIN_0
};

GPIO_ConfigType pin13 =
{
		.GPIO_PinMode = GPIO_OUT,
		.GPIOx = GPIOA,
		.GPIO_PinNumber = GPIO_PIN_13,
		.GPIO_Logic = GPIO_LOW
};

void extISR(void)
{
	MGPIO_voidTogglePortPin(&pin13);
	EXTI_vSetPendingEXTI(EXTI_LINE0);
}

int main(void)
{
	MRCC_voidClockInit(&RCC_obj);
	MRCC_voidPeripheralClockEnable(RCC_APB2_BUS , RCC_GPIOA_CLOCK);
	MRCC_voidPeripheralClockEnable(RCC_APB2_BUS , RCC_AFIO_CLOCK);

	MGPIO_voidInitPortPin(&pin0);
	MGPIO_voidInitPortPin(&pin13);
	AFIO_vEXTI_Configuration(AFIO_LINE0, AFIO_PORTA);

	// Configure the Trigger Detection (Rising) for EXTI0
	EXTI_vSetSignalLatch(EXTI_LINE0, EXTI_TRIGGER_RISING_EDGE);

	// Configure the Call Back for EXTI0
	EXTI_vSetCallBack(EXTI_LINE0, extISR);

	// Event Mask Register
	EXTI_vEnableEXTI(EXTI_LINE0);

	// Enable NVIC IRQ6
	MNVIC_xEnableInterrupt(EXTI0_IRQnum);

	while(1)
	{

	}
}
