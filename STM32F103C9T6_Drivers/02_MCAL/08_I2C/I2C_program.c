/* 
 * File:   I2C_PROGRAM.c
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on June 20, 2024, 8:41 PM
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"


I2C_Config_t g_I2C_Config[2];


void MCAL_I2C_Init(I2Cx_REG* I2Cx,I2C_Config_t* I2C_Config)
{
	uint32 pclk1;

	/* 1. Enable the RCC Clock */
	if(I2Cx == I2C1)
	{
		/* If I2C1 Put all configurations in the global configuration */
		g_I2C_Config[0] = *I2C_Config;
		/* Open the I2C1 RCC Clock */
		I2C1_CLK_EN();
	}
	else if (I2Cx == I2C2)
	{
		/* If I2C2 Put all configurations in the global configuration */
		g_I2C_Config[1] = *I2C_Config;
		/* Open the I2C2 RCC Clock */
		I2C2_CLK_EN();
	}

	/* 2.Program the peripheral input clock in I2C_CR2
	 * Register in order to generate correct timings */
	pclk1 = MRCC_GetPCLK1();
	I2Cx->CR2 |= pclk1 / 1000000;

	/* 3.Configure the clock control registers */
	I2Cx->CCR |= pclk1 / (I2C_Config->Clock_Speed << 1);

	/* 4.Configure the rise time register */
	I2Cx->TRISE = (I2Cx->CR2 & 0x3f) + 1 ;

	/* 5. Enable/Disable Stretch Mode*/
	I2Cx->CR1 |= I2C_Config->Stretch_Mode;

	/* 6. Enable/Disable General Call*/
	I2Cx->CR1 |= I2C_Config->General_Call;

	/* 7. Enable Acknowledge */
	I2Cx->CR1 |= (1<<10);

	/* 8. Set 7-bit Slave Address */
	if(I2C_Config->Slave_Address.Dual_ADD == 0)
	{
		I2Cx->OAR1 = I2C_Config->Slave_Address.Primary_Slave_address << 1;
	}
	else
	{
		I2Cx->OAR1 = I2C_Config->Slave_Address.Primary_Slave_address   << 1;
		I2Cx->OAR2 = I2C_Config->Slave_Address.Secondary_Slave_address << 1 | 1;
	}

	/* 9. Configure Interrupts for (Slave Mode) */
	if(I2C_Config->P_Slave_Event_CallBack != NULL)
	{
		//Enable IRQ
		I2Cx->CR2 |= 0b111<<8;

		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable();
			NVIC_IRQ32_I2C1_ER_Enable();
		}
		else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable();
			NVIC_IRQ34_I2C2_ER_Enable();
		}
	}

	/* 10.Program the I2C_CR1 register to enable the peripheral*/
	I2Cx->CR1 |= 1;
}


void MCAL_I2C_DeInit(I2Cx_REG* I2Cx)
{
	if(I2Cx == I2C1)
	{
		RCC->APB1RSTR |= 1<<21;
		NVIC_IRQ31_I2C1_EV_Disable();
		NVIC_IRQ32_I2C1_ER_Disable();
	}

	else if(I2Cx == I2C2)
	{
		RCC->APB1RSTR |= 1<<22;
		NVIC_IRQ33_I2C2_EV_Disable();
		NVIC_IRQ34_I2C2_ER_Disable();
	}
}


void MCAL_I2C_GPIO_Set_Pins(I2Cx_REG* I2Cx)
{
	GPIO_ConfigType pinCfg;
	pinCfg.GPIO_PinMode = GPIO_PIN_ALTERANTIVE_FUNCTION_OUTPUT_OPENDRAIN_MODE_10MHZ;

	if(I2Cx == I2C1)
	{
		pinCfg.GPIOx = GPIOB;

		pinCfg.GPIO_PinNumber = GPIO_PIN_6;
		MGPIO_voidInitPortPin(&pinCfg);

		pinCfg.GPIO_PinNumber = GPIO_PIN_7;
		MGPIO_voidInitPortPin(&pinCfg);
	}

	else if(I2Cx == I2C2)
	{
		pinCfg.GPIOx = GPIOB;

		pinCfg.GPIO_PinNumber = GPIO_PIN_10;
		MGPIO_voidInitPortPin(&pinCfg);

		pinCfg.GPIO_PinNumber = GPIO_PIN_11;
		MGPIO_voidInitPortPin(&pinCfg);
	}
}


void MCAL_I2C_Master_TX(I2Cx_REG* I2Cx,uint8 slaveAddr,uint8* p_dataOut,uint16 dataLen,Stop_Condition Stop,START_Condition start)
{
	/* 1. Set the start bit in the I2C_CR1 register to generate
	 * a start condition from this will start as master */
	I2C_GenerateSTART(I2Cx,start);

	/* 2. Wait for SB == 1 */
	while(!(I2C_GetFlagStatus(I2Cx,SB)));

	/* 3. Send Address */
	I2C_SendAddress(I2Cx,slaveAddr,write);

	/* 4. Wait for ADDR == 1*/
	while(!(I2C_GetFlagStatus(I2Cx,ADDR)));

	/* 5. Wait for EV8_1 */
	while(!(I2C_GetFlagStatus(I2Cx,EV8_1)));

	/* 6. Send Data*/
	for(int i = 0; i<dataLen; i++)
	{
		I2Cx->DR = p_dataOut[i];
		//Wait for transmit buffer to be empty to send another byte
		while(!(I2C_GetFlagStatus(I2Cx,TxE)));
	}

	/* 7. Wait for Shift register to be empty*/
	while(!(I2C_GetFlagStatus(I2Cx,BTF)));

	/* 8. Send Stop condition */
	if(Stop == with_Stop)
	{
		I2C_GenerateSTOP(I2Cx);
	}
}


void MCAL_I2C_Master_RX(I2Cx_REG* I2Cx,uint8 slaveAddr,uint8* p_datain,uint16 dataLen,Stop_Condition Stop,START_Condition start)
{
	/* 1. Set the start bit in the I2C_CR1 register to generate
	 * a start condition from this will start as master */
	I2C_GenerateSTART(I2Cx,start);

	/* 2. Wait for SB == 1 */
	while(!(I2C_GetFlagStatus(I2Cx,SB)));

	/* 3. Send Address */
	I2C_SendAddress(I2Cx,slaveAddr,read);

	/* 4. Wait for ADDR == 1*/
	while(!(I2C_GetFlagStatus(I2Cx,ADDR)));

	/* 5. Receive the data from slave */
	for(int i = dataLen ; i>=1 ; i--)
	{
		//Wait till the data is received
		while(!(I2C_GetFlagStatus(I2Cx,RxNE)));
		p_datain[i] = I2Cx->DR;

		//if the slave sends The penultimate data -> disable Acknowledgement from master
		if(i == 2)
		{
			I2Cx->CR1 &= ~(1<<10);
		}
	}

	/* 6. Send a stop request */
	if(Stop == with_Stop)
	{
		I2C_GenerateSTOP(I2Cx);
	}

	//re-enable ACK
	I2Cx->CR1 |= (1<<10);
}


void MCAL_I2C_Slave_TX(I2Cx_REG* I2Cx, uint8 TxData)
{
	I2Cx->DR = TxData;
}


uint8 MCAL_I2C_Slave_RX(I2Cx_REG* I2Cx)
{
	return I2Cx->DR;
}


void I2C_GenerateSTART(I2Cx_REG* I2Cx,START_Condition start)
{
	/* Check the type of start (Start or Repeated Start) */
	if(start != Repeated_START )
	{
		//Check if the BUS is idle
		while(I2C_GetFlagStatus(I2Cx,BUSY));
	}

	/* Generate a START condition */
	I2Cx->CR1 |= 1<<8;
}


Flag_Status I2C_GetFlagStatus(I2Cx_REG* I2Cx, Flag flag)
{
	Flag_Status bit_status;
	uint32 event;

	switch(flag)
	{
		case BUSY: 		bit_status = I2Cx->SR2 & 1<<1 ? SET : RESET; break;

		case SB:		bit_status = I2Cx->SR1 & 1 ? SET : RESET; break;

		case ADDR:		bit_status = I2Cx->SR1 & 1<<1 ? SET : RESET; I2Cx->SR2; break;

		case EV8_1:     event = I2Cx->SR1 | I2Cx->SR2 << 16; bit_status = event & EV8_1 ? SET : RESET; break;

		case TxE: 		bit_status = I2Cx->SR1 & 1<<7 ? SET : RESET; break;

		case BTF:		bit_status = I2Cx->SR1 & 1<<2 ? SET : RESET; break;

		case RxNE:		bit_status = I2Cx->SR1 & 1<<6 ? SET : RESET; break;
	}

	return bit_status;
}


void I2C_SendAddress(I2Cx_REG* I2Cx,uint8 slaveAddr,Data_Dir R_W)
{
	if(R_W == write)
	{
		I2Cx->DR = slaveAddr << 1;
	}

	else if(R_W == read)
	{
		I2Cx->DR = slaveAddr << 1 | 1;
	}
}


void I2C_GenerateSTOP(I2Cx_REG* I2Cx)
{
	I2Cx->CR1 |= 1<<9;
}


void I2C1_EV_IRQHandler()
{
	// Handler For interrupt generated by STOPF event
	if(I2C1->SR1 & 1<<4)
	{
		// Stop condition detected
		// Cleared by software reading the SR1 register followed by a write in the CR1 register
		I2C1->CR1 |=0;
		g_I2C_Config[0].P_Slave_Event_CallBack(I2C_EV_STOP);
	}

	// Handler For interrupt generated by ADDR even
	else if(I2C1->SR1 & 1<<1)
	{
		// the received slave address matched with the OAR registers content or a general call
		/* In slave mode, it is recommended to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set. */
		I2C1->SR2;
		g_I2C_Config[0].P_Slave_Event_CallBack(I2C_EV_ADD_MATCHED);
	}

	//  Handler For interrupt generated by TxE event
	else if(I2C1->SR1 & 1<<7)
	{
		//(Master request data from slave)--> slave_transmitter
		g_I2C_Config[0].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
	}

	//  Handler For interrupt generated by RxE event
	else if(I2C1->SR1 & 1<<6)
	{
		//(slave receive data)-->slave_Receiver
		g_I2C_Config[0].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
	}
}


void I2C1_ER_IRQHandler(){

}


void I2C2_EV_IRQHandler()
{
	// Handler For interrupt generated by STOPF event
	if(I2C2->SR1 & 1<<4)
	{
		// Stop condition detected
		// Cleared by software reading the SR1 register followed by a write in the CR1 register
		I2C2->CR1 |=0;
		g_I2C_Config[1].P_Slave_Event_CallBack(I2C_EV_STOP);
	}

	// Handler For interrupt generated by ADDR even
	else if(I2C2->SR1 & 1<<1)
	{
		// the received slave address matched with the OAR registers content or a general call
		/* In slave mode, it is recommended to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set. */
		I2C2->SR2;
		g_I2C_Config[1].P_Slave_Event_CallBack(I2C_EV_ADD_MATCHED);
	}

	//  Handler For interrupt generated by TxE event
	else if(I2C2->SR1 & 1<<7)
	{
		//(Master request data from slave)--> slave_transmitter
		g_I2C_Config[1].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
	}

	//  Handler For interrupt generated by RxE event
	else if(I2C2->SR1 & 1<<6)
	{
		//(slave receive data)-->slave_Receiver
		g_I2C_Config[1].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
	}
}


void I2C2_ER_IRQHandler(){

}

