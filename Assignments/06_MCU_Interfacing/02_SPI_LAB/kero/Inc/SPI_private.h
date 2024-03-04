/* 
 * File:   SPI_PRIVATE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on Febreuary 16, 2024, 8:41 PM
 */

#ifndef __SPI_PRIVATE_H__
#define __SPI_PRIVATE_H__
	
typedef struct
{
  volatile uint32 CR1;
  volatile uint32 CR2;
  volatile uint32 SR;
  volatile uint32 DR;
  volatile uint32 CRCPR;
  volatile uint32 RXCRCR;
  volatile uint32 TXCRCR;
  volatile uint32 I2SCFGR;
  volatile uint32 I2SPR;
} SPI_t;


#define SPI1_BASE_ADDRESS			0x40013000
#define SPI2_BASE_ADDRESS			0x40013000
#define SPI3_BASE_ADDRESS			0x40013000
						 
						 
#define SPI1						((SPI_t*)  SPI1_BASE_ADDRESS)
#define SPI2                        ((SPI_t*)  SPI2_BASE_ADDRESS)
#define SPI3                        ((SPI_t*)  SPI3_BASE_ADDRESS)


#endif  __SPI_PRIVATE_H__