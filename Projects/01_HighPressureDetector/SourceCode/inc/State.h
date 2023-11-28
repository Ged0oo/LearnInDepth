#ifndef __STATE_H__
#define __STATE_H__


#include <stdio.h>
#include <stdlib.h>
#include "driver.h"


#define State_Define(_STFUNC_) void ST_##_STFUNC_()
#define State(_STFUNC_) ST_##_STFUNC_


void Set_Pressure_Value(int Pressure_Value); 
void High_Pressure_Detected();               
void Start_Alarm();                          
void Stop_Alarm();                           


#endif // __STATE_H__