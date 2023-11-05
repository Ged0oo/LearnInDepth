//*Platform types for STMicroelectronics ST30 realtive to ANSI C types
#ifndef __PLATFORM_TYPES_H__
#define __PLATFORM_TYPES_H__

#define CPU_TYPE        CPU_TYPE_32
#define CPU_BIT_ORDER   MSB_FIRST
#define CPU_BYTE_ORDER  HIGH_BYTE_FIRST

#define 	unsigned char                 uint8;
#define 	unsigned short                uint16;
#define 	unsigned long                 uint32;
#define 	unsigned long long            uint64;

#define 	signed char                   sint8;
#define 	signed short                  sint16;
#define 	signed long                   sint32;
#define 	signed long long              sint64;

#define 	volatile unsigned char        vuint8;
#define 	volatile unsigned short       vuint16;
#define 	volatile unsigned long        vuint32;
#define 	volatile unsigned long long   vuint64;

#define 	volatile signed char          vsint8;
#define 	volatile signed short         vsint16;
#define 	volatile signed long          vsint32;
#define 	volatile signed long long     vsint64;

#define 	unsigned char                 boolean;
#define 	float                         float32;
#define 	double                        float64;

#endif