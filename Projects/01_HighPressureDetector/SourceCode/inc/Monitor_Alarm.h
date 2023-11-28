#ifndef __MONITOR_ALARM_H__
#define __MONITOR_ALARM_H__

#include "State.h"


enum 
{
    MoA_Alarm_OFF ,
    MoA_Alarm_ON  ,
    MoA_Waiting
}MoA_State_id;


State_Define(MoA_Alarm_OFF);
State_Define(MoA_Alarm_ON);
State_Define(MoA_Waiting);


extern void(*MoA_State)();


#endif //__MONITOR_ALARM_H__