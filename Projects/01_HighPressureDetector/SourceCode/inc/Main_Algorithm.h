#ifndef __MAIN_ALGORITHM_H__
#define __MAIN_ALGORITHM_H__

#include "State.h"

enum
{
    MA_High_Pressure_Detect
}MA_State_id ;


State_Define(MA_High_Pressure_Detect);


extern void (*MA_State)() ;


#endif //MAIN_ALGORITHM_H_