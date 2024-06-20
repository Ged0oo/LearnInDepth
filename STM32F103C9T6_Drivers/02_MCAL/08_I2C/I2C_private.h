/* 
 * File:   I2C_PRIVATE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on June 20, 2024, 8:41 PM
 */


#ifndef __I2C_PRIVATE_H__
#define __I2C_PRIVATE_H__
	

#include "STD_TYPES.h"


typedef struct
{
	vuint32 CR1;
	vuint32 CR2;
	vuint32 OAR1;
	vuint32 OAR2;
	vuint32 DR;
	vuint32 SR1;
	vuint32 SR2;
	vuint32 CCR;
	vuint32 TRISE;
}I2Cx_REG;


#define I2C1_BASE		0x40005400UL
#define I2C2_BASE		0x40005800UL


#define I2C1			((I2Cx_REG  *)I2C1_BASE)
#define I2C2			((I2Cx_REG  *)I2C2_BASE)


#endif  __I2C_PRIVATE_H__
