#ifndef __PRESSURE_SENSOR_H__
#define __PRESSURE_SENSOR_H__
#include "State.h"


enum
{
    PS_Reading ,
    PS_Waiting
}PS_State_id;


void PS_init();
State_Define(PS_Reading);
State_Define(PS_Waiting);


extern void (*PS_State)() ;


#endif //__PRESSURE_SENSOR_H__