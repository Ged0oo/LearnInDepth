/* 
 * File:   I2C_INTERFACE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on June 20, 2024, 8:41 PM
 */


#ifndef __I2C_INTERFACE_H__
#define __I2C_INTERFACE_H__

#include "I2C_private.h"
#include "RCC_private.h".h"
#include "NVIC_private.h"s


//Enable I2Cx Clocks
#define I2C1_CLK_EN()	 RCC->APB1ENR |= 1<<21
#define I2C2_CLK_EN()	 RCC->APB1ENR |= 1<<22


//Enable I2Cx IRQs
#define NVIC_IRQ31_I2C1_EV_Enable()		NVIC_ISER0 |=1<<31
#define NVIC_IRQ32_I2C1_ER_Enable()		NVIC_ISER1 |=1<<0
#define NVIC_IRQ33_I2C2_EV_Enable()		NVIC_ISER1 |=1<<1
#define NVIC_IRQ34_I2C2_ER_Enable()		NVIC_ISER1 |=1<<2
#define NVIC_IRQ31_I2C1_EV_Disable()	NVIC_ICER0 |=1<<31
#define NVIC_IRQ32_I2C1_ER_Disable()	NVIC_ICER1 |=1<<0
#define NVIC_IRQ33_I2C2_EV_Disable()	NVIC_ICER1 |=1<<1
#define NVIC_IRQ34_I2C2_ER_Disable()	NVIC_ICER1 |=1<<2


typedef enum
{
	I2C_EV_STOP,
	I2C_EV_ADD_MATCHED,
	I2C_EV_DATA_REQ,				// APP_Layer should send data (MCAL_I2C_Slave_TX)
	I2C_EV_DATA_RCV					// APP_Layer should receive data (MCAL_I2C_Slave_RX)
}Slave_State;

typedef enum
{
	with_Stop,
	without_Stop

}Stop_Condition;

typedef enum
{
	START,
	Repeated_START

}START_Condition;

typedef enum
{
	RESET,
	SET

}Flag_Status;

typedef enum
{
	BUSY,
	SB,
	ADDR,
	TxE,
	BTF,
	RxNE,
	EV8_1 = 0x00070080
}Flag;

typedef enum
{
	write,
	read
}Data_Dir;

typedef struct
{
	uint8 Dual_ADD;					//1-Enable 0-Disable
	uint8 Primary_Slave_address;		//7-bit mode only
	uint8 Secondary_Slave_address;	//7-bit mode only
}I2C_Slave_address_t;

typedef struct
{
	uint32  				Clock_Speed;				// Specifies I2C clock speed
														// This parameter must be set based on @ref I2C_CLOCK_SPEED_DEFINE

	uint8					Stretch_Mode;				// specifies Enable or Disable clock stretching in slave mode only
														// This parameter must be set based on @ref I2C_STRETCH_MODE_DEFINE

	I2C_Slave_address_t		Slave_Address;

	uint8					General_Call;				// specifies Enable or Disable General_Call
														// This parameter must be set based on @ref I2C_GENERAL_CALL_DEFINE

	void(*P_Slave_Event_CallBack)(Slave_State); 		// Set the C Function which will be called once IRQ Happens

}I2C_Config_t;

//@ref I2C_CLOCK_SPEED_DEFINE
#define I2C_SCLK_SM_50K				50000U
#define I2C_SCLK_SM_100K			100000U

//@ref I2C_STRETCH_MODE_DEFINE
#define I2C_StretchMode_Enable		0
#define I2C_StretchMode_Disable		1<<7

//@ref I2C_GENERAL_CALL_DEFINE
#define I2C_GENERAL_CALL_Enable		1<<6
#define I2C_GENERAL_CALL_Disable	0

void MCAL_I2C_Init(I2Cx_REG* I2Cx,I2C_Config_t* I2C_Config);
void MCAL_I2C_DeInit(I2Cx_REG* I2Cx);
void MCAL_I2C_GPIO_Set_Pins(I2Cx_REG* I2Cx);
void MCAL_I2C_Master_TX(I2Cx_REG* I2Cx,uint8 slaveAddr,uint8* p_dataOut,uint16 dataLen,Stop_Condition Stop,START_Condition start);
void MCAL_I2C_Master_RX(I2Cx_REG* I2Cx,uint8 slaveAddr,uint8* p_datain,uint16 dataLen,Stop_Condition Stop,START_Condition start);
void MCAL_I2C_Slave_TX(I2Cx_REG* I2Cx, uint8 TxData);
uint8 MCAL_I2C_Slave_RX(I2Cx_REG* I2Cx);

void I2C_GenerateSTART(I2Cx_REG* I2Cx,START_Condition start);
Flag_Status I2C_GetFlagStatus(I2Cx_REG* I2Cx, Flag flag);
void I2C_SendAddress(I2Cx_REG* I2Cx,uint8 slaveAddr,Data_Dir R_W);
void I2C_GenerateSTOP(I2Cx_REG* I2Cx);

#endif  __I2C_INTERFACE_H__
